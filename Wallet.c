

#include "Wallet.h"
#include "Tree.h"
#include "Transaction.h"


struct wallet_list* new_wallet(struct wallet temp){			//Constructor function

	struct wallet_list* new=malloc(sizeof(struct wallet_list));
	new->wallie=temp;
    new->wallie.total_sum=0;
    new->next=NULL;
    new->wallie.ulr=NULL;

	return (new);	

}

struct wallet_list* get_last_wallet(struct wallet_list* wt){ //Getting the last user of the list

		while(wt->next != NULL){
          wt = wt->next;
        }

        return wt;
}

void calculate_sum(struct wallet_list* wt){ //Function used to get his total money 

	while(wt !=NULL){
      
      if(wt->wallie.ulr!=NULL){
        
        struct bit_list* utemp=wt->wallie.ulr;
        while (utemp!=NULL){
        
        wt->wallie.total_sum=wt->wallie.total_sum+utemp->bp->data;
        utemp=utemp->next;
        }
        
      }

      wt=wt->next;
    }

}

int how_many(struct wallet_list* wt, struct trans_list* tt){ //How many function checks how many bitcoins will be used in one transaction

//Generally the program behaves differently if we have to use one bitcoin or more so this function is used to know which functions we"ll use later on
	
	int more=0;

	while(wt!=NULL){
        if(strcmp(wt->wallie.ID,tt->trans.sender_ID)==0){ //We find the sender in the list 

          struct bit_list* utempt=wt->wallie.ulr;

          if(tt->trans.amount>wt->wallie.ulr->bp->data){ //If transaction's amount is more than the first bitcoin in the list we"ll have to use more than that

            more=1;
            break; 

          }else{ //Otherwise we"re free to use simply the first one 

            more=0;
            break;
        
          }
        }
        wt=wt->next;
      }
      return more;
}

//If we're using one bitcoin
struct tree_node* get_bitcoin(struct wallet_list* wt, struct trans_list* tt){  //This function returns the bitcoin that will be used
	struct tree_node* hold;
	while(wt!=NULL){
        if(strcmp(wt->wallie.ID,tt->trans.sender_ID)==0){

          struct bit_list* utempt=wt->wallie.ulr;
          hold=utempt->bp;
          break;
          }
          wt=wt->next;
      }
      return hold;

}

//If we're using more than one we are creating a list 
struct bit_list* get_bitcoin_list(struct wallet_list* wt, struct trans_list* tt){
	struct bit_list* templist;
	int remaining=0;

	while(wt!=NULL){
        if(strcmp(wt->wallie.ID,tt->trans.sender_ID)==0){ 
        	struct bit_list* utempt=wt->wallie.ulr;


            remaining=tt->trans.amount-utempt->bp->data; //We create a list and we add the first bitcoin
            templist=malloc(sizeof(struct bit_list));

            templist->bp=utempt->bp;
            templist->next=NULL;
            utempt=utempt->next;
           

            struct bit_list* tempplist=templist;
            while(1){
            if(remaining>utempt->bp->data){ //If remaining is more than the value of the bitcoin we are checking, we add it to the list then we subtract the value of the next one
               
              struct bit_list* newbnode=malloc(sizeof(struct bit_list));
			  
              newbnode->bp=utempt->bp;
              newbnode->next=NULL;
              tempplist->next=newbnode;
              tempplist=tempplist->next;

              if(utempt->next!=NULL){ //If there is no next node in the list it means that we will use all the bitcoins, so we exit the loop 
              utempt=utempt->next;
              remaining=remaining-utempt->bp->data;
              continue;
          	  }else{
          	  	break;
          	  }
              
              
            }else{ //If remaining is less or equal to the bitcoin's data we add it to the list and exit the loop since we won't use any more bitcoins
            	
               
              struct bit_list* newbnode=malloc(sizeof(struct bit_list));
              newbnode->bp=utempt->bp;
              newbnode->next=NULL;

              tempplist->next=newbnode;

              break;
            }
            }

            break;  
          }
           wt=wt->next;
        }
       return templist;

}

void update_sender_one(struct wallet_list* wt, struct trans_list* tt, struct tree_node* hold ){ //Updating sender's wallet if one bicoin is used
	
	while(wt!=NULL){
        if(strcmp(wt->wallie.ID,tt->trans.sender_ID)==0){ 


          struct bit_list* utemp=wt->wallie.ulr; //The first bitcoin from the list is removed
          struct bit_list* tnext=utemp->next;
          free(utemp);
          wt->wallie.ulr=tnext;

          if(wt->wallie.ulr==NULL){ //If the list is NULL this means there was only one bitcoin so we have to create ta new list 

            if(hold->right!=NULL){ //If the right node is NULL this means this user doesn't have this bitcoin anymore, so we don't add anything
            
            struct bit_list* new_node=malloc(sizeof(struct bit_list)); //Otherwise we add the the right tree node since this has the remaining value
            new_node->bp=hold->right;     
            new_node->next=NULL;
            wt->wallie.ulr=new_node;
            wt->wallie.ulr->next=NULL;


            wt->wallie.total_sum=hold->right->data; //and we get his new total money 
            }else{
              wt->wallie.total_sum=0;
            }

            
          }else{ //If the list is not NULL after deleting the first node we add the new right node at the end of the list


          struct bit_list* utemp1=wt->wallie.ulr;

          while(utemp1->next != NULL){
              utemp1 = utemp1->next;
          }
            
          struct bit_list* new_node=malloc(sizeof(struct bit_list));
          new_node->bp=hold->right;
          new_node->next=NULL;
          utemp1->next=new_node;


            wt->wallie.total_sum=0; //Getting the total money anew
            struct bit_list* utemp2=wt->wallie.ulr;
            while (utemp2!=NULL){
              
            wt->wallie.total_sum=wt->wallie.total_sum+utemp2->bp->data;
            utemp2=utemp2->next;
            }
        }
          
        

        }
        wt=wt->next;
      }
}

void update_sender_many(struct wallet_list* wt, struct trans_list* tt, struct bit_list* templist){ //Updating sender's wallet if a bitcoin list was used


      while(wt!=NULL){
        if(strcmp(wt->wallie.ID,tt->trans.sender_ID)==0){  


            struct bit_list* pare=templist;
            struct bit_list* utempare=wt->wallie.ulr;
            while(pare!=NULL){
                
            if(strcmp(utempare->bp->ID,pare->bp->ID)==0){ //Getting the right bitcoins
           
              if(pare->bp->right==NULL){  //If there is no right node then it is removed completely from the list 
                
                struct bit_list* tnext=utempare->next;

                free(utempare);
                wt->wallie.ulr=tnext;
                utempare=wt->wallie.ulr;
                

                pare=pare->next;
              

              }else{              //Otherwise the right node is placed at the end
                    
                struct bit_list* tnext=utempare->next; //Removing the old one 
                free(utempare);
                wt->wallie.ulr=tnext;

                struct bit_list* utemp1=wt->wallie.ulr;

                if(utemp1!=NULL){ //If there are still bitcoins left place it at the end 
                 while(utemp1->next != NULL){
                  utemp1 = utemp1->next;
                  }
                

                struct bit_list* new_node=malloc(sizeof(struct bit_list));
                new_node->bp=pare->bp->right;
                new_node->next=NULL;
                utemp1->next=new_node;

              	}else{ //Otherwisw create a new list

                  struct bit_list* new_node=malloc(sizeof(struct bit_list));
                  new_node->bp=pare->bp->right;
                  new_node->next=NULL;
                  utemp1=new_node;
                  wt->wallie.ulr=utemp1;

                  wt->wallie.total_sum=pare->bp->right->data;//New total money
                  
              }

                break;
              }

            }

            }


            wt->wallie.total_sum=0; //Getting the total money anew
            struct bit_list* utemp2=wt->wallie.ulr;
            if(utemp2!=NULL){
              while (utemp2!=NULL){
              wt->wallie.total_sum=wt->wallie.total_sum+utemp2->bp->data;
              utemp2=utemp2->next;
              }
            }


          

        }
        wt=wt->next;
      }

}

void update_receiver_one(struct wallet_list* wt, struct trans_list* tt, struct tree_node* hold){ //Updating receiver's wallet if one bitcoin was used
	bool found1=0;
      while(wt!=NULL){
        if(strcmp(wt->wallie.ID,tt->trans.receiver_ID)==0){
		

          struct bit_list* utemp=wt->wallie.ulr;
          if(utemp==NULL){ //If list head is NULL then he has no bitcoins so we"ll create his list, and add the left node that was created

            struct bit_list* new_node=malloc(sizeof(struct bit_list));
            new_node->bp=hold->left;
            new_node->next=NULL;
            utemp=new_node;
            wt->wallie.ulr=utemp;

            wt->wallie.total_sum=hold->left->data;//New total money
            
            
            
          }else{ //If he has at least one bitcoin

          while(utemp!=NULL){
            if(strcmp(utemp->bp->ID,hold->ID)==0){ //If he already has this bitcoin don't add anything, just update its value. The original value is unaffected
              utemp->bp->data=utemp->bp->data+hold->left->data;
              found1=1;
              break;
            }
            utemp=utemp->next;
          }
          if(found1==0){ //Bitcoin doesn't exist, add it at the end of the list
            utemp=wt->wallie.ulr;
            while(utemp->next != NULL){
              utemp = utemp->next;
            }
            struct bit_list* new_node=malloc(sizeof(struct bit_list));
            new_node->bp=hold->left;
            new_node->next=NULL;
            utemp->next=new_node;

            wt->wallie.total_sum=0; //New total money
            struct bit_list* utemp2=wt->wallie.ulr;
            while (utemp2!=NULL){
       
            wt->wallie.total_sum=wt->wallie.total_sum+utemp2->bp->data;
            utemp2=utemp2->next;
            }
          }

        }

        
      }
        wt=wt->next;
      }



}

void update_receiver_many(struct wallet_list* wt, struct trans_list* tt, struct bit_list* templist){ //Updating receiver's wallet if a bitcoin list was used

	bool found1=0;
      while(wt!=NULL){
        if(strcmp(wt->wallie.ID,tt->trans.receiver_ID)==0){

          
            struct bit_list* pare=templist;
            struct bit_list* utempare=wt->wallie.ulr;
            while(pare!=NULL){
              if(utempare==NULL){ //If list head is NULL create the first node 

              struct bit_list* new_node=malloc(sizeof(struct bit_list));
              new_node->bp=pare->bp->left;
              new_node->next=NULL;
              utempare=new_node;
              wt->wallie.ulr=utempare;
              wt->wallie.total_sum=pare->bp->left->data;
              pare=pare->next;

            }else{ //If he has at least one bitcoin
              while(utempare->next != NULL){
              utempare = utempare->next;
              } //Get the last node
              if(strcmp(utempare->bp->ID,pare->bp->ID)==0){ //If he already has this bitcoin don't add anything, just update its value. The original value is unaffected
                  utempare->bp->data=utempare->bp->data+pare->bp->left->data;
                  pare=pare->next;
              }else{ //Bitcoin doesn't exist, add it at the end of the list

              struct bit_list* new_node=malloc(sizeof(struct bit_list));
              new_node->bp=pare->bp->left;
              new_node->next=NULL;
              utempare->next=new_node;
             
              pare=pare->next;
            }

            }
            
            }


            wt->wallie.total_sum=0; //New total money
            struct bit_list* utemp2=wt->wallie.ulr;
      
            while (utemp2!=NULL){
              
            wt->wallie.total_sum=wt->wallie.total_sum+utemp2->bp->data;
            
            utemp2=utemp2->next;
            }

            
          
      }
        wt=wt->next;
      }


} 


void DestroyWalletList(struct wallet_list* wroot){ //Deleting the list with the users


	struct wallet_list* wtemp2=wroot;
    struct wallet_list* curr=wtemp2;
    struct wallet_list* next;

      while(curr !=NULL){

        next=curr->next;
        free(curr);
        curr=next;

      }
}

int check_userid(struct wallet_list* wroot, char* ID){ //Function to check if the user from the transactionsFile exists


	int isvalid=1;
	int yes=0;
      struct wallet_list* stekei=wroot;
      while(stekei!=NULL){
        if(strcmp(stekei->wallie.ID,ID)==0){

          yes=1;
          break;
        }
        stekei=stekei->next;
      }

      if(yes==0){

        isvalid=0;
      }
      return isvalid;
}

int check_amount(struct wallet_list* wroot, char* ID,int amount){ //Function to check if he has enough money to complete the transactions

	int isvalid=1;
	struct wallet_list* stekei=wroot;
      while(stekei !=NULL){
        if(strcmp(stekei->wallie.ID,ID)==0){
          
          if(stekei->wallie.total_sum<amount){
            isvalid=0;
            break;
          }

        }
      
        stekei=stekei->next;
      }

      return isvalid;


}


int is_same(char* ID1,char* ID2){ //Function to check if the sender is same as the receiver

		int sfailure=0;
	
        if(strcmp(ID1,ID2)==0){

          sfailure=1;
       }

      return sfailure;

}
