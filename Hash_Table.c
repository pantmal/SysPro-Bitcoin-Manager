
#include "Hash_Table.h"
#include "Transaction.h"


int hash_func(char* user, int entries){   //Hash to function to see in which cell the user will be placed
	
	  int t=0;
      int value=0;
      while(user[t]!='\0'){
        value=value+user[t];
        t++;
      }

      return value%entries;
	
}

void add_first(struct bucket_list* buckettemp, struct trans_list* tt, int bucketsize, int sr){ //If user's key does not exist, add_first is called to place him in the first spot

		
        buckettemp->next=NULL;
        buckettemp->isfull=0;
        buckettemp->counter=0;
        buckettemp->bucket=NULL;       
           
      buckettemp->bucket=malloc(bucketsize * sizeof(struct bucket_data)); //Create the bucket
      int b=0;
      for(b;b<bucketsize;b++){
        buckettemp->bucket[b].ID=NULL;
        buckettemp->bucket[b].root=NULL;
      }

      if(sr==0){ //sr flag is used for sender/receiver
      buckettemp->bucket[0].ID=tt->trans.sender_ID;
  	  }
  	  if(sr==1){
  	  buckettemp->bucket[0].ID=tt->trans.receiver_ID;		
  	  }
      buckettemp->bucket[0].root=malloc(sizeof(struct trans_list_hash));
      buckettemp->bucket[0].root->next=NULL;
      buckettemp->bucket[0].root->t1=&tt->trans;
      buckettemp->counter++;
      if(buckettemp->counter==bucketsize){
        buckettemp->isfull=1;
      }



}


struct trans_list_hash* search(struct bucket_list* buckettemp, char* user, int bucketsize ){ //Search function searches the user in the hash table

	int sfound = 0;
	int byes=0;
	while(buckettemp!=NULL){
          
          for(byes;byes<bucketsize;byes++){

          if(buckettemp->bucket[byes].ID==NULL){
            
            break;
          }
          if(strcmp(buckettemp->bucket[byes].ID,user)==0){
            
            sfound=1;
            break;

          }

        }

        if(sfound==1){
          break;
        }
        

        buckettemp=buckettemp->next;

         if(sfound==0){
          byes=0;
          continue;
        }
 

        }
 
        if(sfound==1){ //If he exists return the head of his transactions list
    	    return buckettemp->bucket[byes].root;
    	}else if(sfound==0){
    		return NULL;
    	}

}


void add_existing(struct trans_list_hash* bucket_root, struct trans_list* tt){ //Add existing places a transaction to an already existing user

			struct trans_list_hash* ntemp=bucket_root;
          
            while(ntemp->next!=NULL){

              ntemp=ntemp->next;
            }
            struct trans_list_hash* nntemp;
            nntemp=malloc(sizeof(struct trans_list_hash));
            nntemp->next=NULL;
            nntemp->t1=&tt->trans;
          
       
            ntemp->next=nntemp;
         
}

void add_free(struct bucket_list* buckettemp, struct trans_list* tt, int bucketsize, int sr){ //Add free places the user in the first free spot it finds

          
          while(1){

          int pos=0;
          if(buckettemp->isfull==0){ //If it's not full place him here
              int b=0;
              for(b;b<bucketsize;b++){
                if(buckettemp->bucket[b].ID==NULL){
                  pos=b;
                  break;
                }
              }
              if(sr==0){//sr flag is used for sender/receiver
              buckettemp->bucket[pos].ID=tt->trans.sender_ID;
          	  }
          	  if(sr==1){
          	  buckettemp->bucket[pos].ID=tt->trans.receiver_ID;	
          	  }
              buckettemp->bucket[pos].root=malloc(sizeof(struct trans_list_hash));

              buckettemp->bucket[pos].root->next=NULL;
              buckettemp->bucket[pos].root->t1=&tt->trans;
              
              buckettemp->counter++;
              if(buckettemp->counter==bucketsize){
                buckettemp->isfull=1;
              }
              break;

          }else if(buckettemp->isfull==1){ //Create the next one if he can't fit

            if(buckettemp->next==NULL){ //Since the node does not exist create it and place him in the first spot
              buckettemp->next=malloc(sizeof(struct bucket_list));
              buckettemp=buckettemp->next;
              buckettemp->next=NULL;
              buckettemp->isfull=0;
              buckettemp->counter=0;
              buckettemp->bucket=NULL;
              buckettemp->bucket=malloc(bucketsize * sizeof(struct bucket_data));
              int b1=0;
              for(b1;b1<bucketsize;b1++){
                buckettemp->bucket[b1].ID=NULL;
                buckettemp->bucket[b1].root=NULL;
              }
              int b=0;
              for(b;b<bucketsize;b++){
                if(buckettemp->bucket[b].ID==NULL){
                  pos=b;
                  break;
                }
              }
              if(sr==0){//sr flag is used for sender/receiver
              buckettemp->bucket[pos].ID=tt->trans.sender_ID;
          	  }
          	  if(sr==1){
              buckettemp->bucket[pos].ID=tt->trans.receiver_ID;
          	  }

             
              buckettemp->bucket[pos].root=malloc(sizeof(struct trans_list_hash));

              buckettemp->bucket[pos].root->next=NULL;
              buckettemp->bucket[pos].root->t1=&tt->trans; 
              buckettemp->counter++;
              if(buckettemp->counter==bucketsize){
                buckettemp->isfull=1;
              }
              break;
            }
            
            buckettemp=buckettemp->next;

          }

        }



}