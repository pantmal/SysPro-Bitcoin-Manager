
#include "Tree.h"
#include "Transaction.h"


struct tree_node* newnode(int n, char* ID, char* user){			//Constructor function

	struct tree_node* new=malloc(sizeof(struct tree_node));
	new->data= n;
	new->left= NULL;
	new->right=NULL;

	strcpy(new->ID,ID);
	strcpy(new->user,user);

	return (new);	

}


int find_right_most(struct tree_node* rt){ //find_right_most is used in the traceCoin command to find the unspent value

	while(rt->right!=NULL){ //It reaches the right-most node
		rt=rt->right;
	}
	if(rt->right==NULL){ 
		if(rt->allspent==1){ //If allspent is 1 this means all of its original value was spent 
			return 0;
		}else{
			return rt->originaldata; //Otherwise its original data is the unspent value
		}
	}
	
	
}



void display(struct tree_node* ptr){ //Display is used in the traceCoin command to print all the transactions 
	if(ptr == NULL){  //It uses a DFS algorithm to search all the nodes
		return;
	}
	display(ptr->left);
	
	if(ptr->isleft==1){ //If it is a left node this means a transaction took place with this bitcoin
    struct transaction* temp= ptr->transp;
    print_transaction(*temp);
	}
	display(ptr->right);
}

void get_num_of_trans(struct tree_node* ptr,int* g){ //Same DFS algorithm is used in this function to calculate the number of transactions
	
	if(ptr == NULL){
		return ;
	}
	get_num_of_trans(ptr->left,g);
	if(ptr->isleft==1){ //If it is a left node it means a transaction took place (Note: Only left nodes are taken into account because if the entire bitcoin data was used in a transaction no right node will be created)
		*g=*g+1; 
	}
	get_num_of_trans(ptr->right,g);
	
}


struct bit_list* get_last_bit(struct bit_list* bt){ //Getting the last bitcoin from a bitcoin list 

		while(bt->next != NULL){
          bt = bt->next;
        }

        return bt;

}

void break_bitcoin(struct tree_node* hold, struct trans_list* thold ){ //Break will generate the new left (and right if needed nodes) if only one bitcoin was used in a transaction
		
		      int valoff=hold->data - thold->trans.amount; //Valoff is the data that will be passed to the right node (if it will be created)

          hold->left=newnode(thold->trans.amount,hold->ID,thold->trans.receiver_ID); //Left node is created here
          hold->left->originaldata=thold->trans.amount; 
          hold->left->isleft=1;
          hold->left->left=NULL;
          hold->left->right=NULL;
          hold->left->transp=&thold->trans; //All left nodes have pointers to transaction struct
          
          if(valoff!=0){ //Create a right node only if it still has value
            hold->right=newnode(valoff,hold->ID,thold->trans.sender_ID);
            hold->right->originaldata=valoff;
            hold->right->isright=1;
            hold->right->left=NULL;
            hold->right->right=NULL;  
          }else{  //Otherwise don't create one and set it as allspent for the traceCoin Command
            hold->right=NULL;
            hold->allspent=1;
          }

}

void break_bitcoin_list(struct bit_list* templist, struct trans_list* thold ){ //Different function is used if more than one bitcoins are used in one transaction

			      struct bit_list* spase=templist; //Templist has the bitcoins used in the transaction
            int valoff=thold->trans.amount; //Valoff gets the amount needed
            while(spase!=NULL){
              

              if(valoff>spase->bp->data){ //If the amount is bigger than the bitcoin's value we are checking
                
                spase->bp->allspent=1; //All of it will be used
                spase->bp->left=newnode(spase->bp->data,spase->bp->ID,thold->trans.receiver_ID); //A left node will be created
                spase->bp->left->originaldata=spase->bp->data; 
                spase->bp->right=NULL; //But not a right node since all of it was used 
                spase->bp->left->isleft=1;
                spase->bp->left->left=NULL;
                spase->bp->left->right=NULL;
                spase->bp->left->transp=&thold->trans; //Getting the transaction

                valoff=valoff-spase->bp->data; //Now subtract bitcoin's value from the amount and compare the remaining amount with the other bitcoins
               
                spase=spase->next;

              }else{ //If it is not bigger this means that is the last bitcoin we will break
                
                spase->bp->left=newnode(valoff,spase->bp->ID,thold->trans.receiver_ID); //Create the left node
                spase->bp->left->originaldata=valoff;
                spase->bp->left->isleft=1;
                spase->bp->left->left=NULL;
                spase->bp->left->right=NULL;
                spase->bp->left->transp=&thold->trans;
                if(spase->bp->data==valoff){ //If the remaining amount is equal to its data this mean we"ll have to use all of it so no right node will be created
                  spase->bp->right=NULL;  
                  spase->bp->allspent=1;
                }else{ //Otherwise create the right node
                  spase->bp->right=newnode(spase->bp->data-valoff,spase->bp->ID,thold->trans.sender_ID);
                  spase->bp->right->originaldata=spase->bp->data-valoff;
                  spase->bp->right->isright=1;
                  spase->bp->right->left=NULL;
                  spase->bp->right->right=NULL;
                }

                break;
                

              }
            }

}



void DestroyTree(struct tree_node* root){ //Deleting a tree
    if (!root) {return;}
    DestroyTree(root->left);
    DestroyTree(root->right);
    free(root);      
}


void DestroyBitList(struct bit_list* broot){ //Deleting a bitcoin list


    struct bit_list* btemp3=broot;
    struct bit_list* bcurr=btemp3;
    struct bit_list* bbnext;

      while(bcurr !=NULL){

        bbnext=bcurr->next;
        free(bcurr);
        bcurr=bbnext;

      }
}