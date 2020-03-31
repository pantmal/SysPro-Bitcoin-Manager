#include <string.h>

#include "Transaction.h"



struct trans_list* get_last_trans(struct trans_list* trt){ //Getting the last node of the transaction list

	while(trt->next != NULL){
          trt = trt->next;
        }

        return trt;
}

int check_times(struct time t1, struct time t2){ //Checking times. If t1's hour is bigger the transaction with t1 will proceed. If it's smaller it won't. If it's the same hour check the same the minutes

	
	if(t1.hour>t2.hour){
		return 1;
	}
	if(t1.hour<t2.hour){
		return 0;
	}
	if(t1.hour==t2.hour){
		if(t1.mins>t2.mins){
			return 1;
		}
		if(t1.mins<t2.mins || t1.mins==t2.mins ){ //Transactions cannot take place at the same minute
			return 0;
		}
	}


}

int check_dates(struct date d1, struct date d2 ){ //Similar logic to check the dates. If year is bigger procced, if smaller do not, if they are equal check for months and so on

	if(d1.year>d2.year){
        
        return 1;

      }

      if(d1.year<d2.year){

       
        return 0;
      } 

      if(d1.year==d2.year){
        
        if(d1.month>d2.month){
          
          return 1;	
        }
        if(d1.month<d2.month){
          
        	return 0;
        }
        if(d1.month==d2.month){
          if(d1.day>d2.day){
            
            return 1;
          }
          if(d1.day<d2.day){
           
            return 0;
          }
          if(d1.day==d2.day){ //If everything is the same return 2 to call check times function
          	return 2;
          }

        }
      }


}

void DestroyTransactionList(struct trans_list* troot){ //Destroying the list with the transactions


	struct trans_list* trrr=troot;
    struct trans_list* tcurr=trrr;
    struct trans_list* ttnext;

      while(tcurr !=NULL){

        ttnext=tcurr->next;
        free(tcurr);
        tcurr=ttnext;

      }
}

int check_id(char* ID,struct trans_list* troot){ //Check if transaction's id already exists 

	int failure=0;
	if(troot!=NULL){
        struct trans_list* stekei=troot;
        while(stekei!=NULL){
        if(strcmp(ID,stekei->trans.ID)==0){

          printf("Failure\n");
          failure=1;

          break;
        }
        stekei=stekei->next;
      }
      }

     return failure;

}

void print_transaction(struct transaction tp){ //Print transaction's information

	printf("%s %s %s %d ",tp.ID, tp.sender_ID, tp.receiver_ID, tp.amount);
	printf("%d-%d-%d ", tp.tdate.day, tp.tdate.month, tp.tdate.year );
	printf("%d:%d\n", tp.ttime.hour, tp.ttime.mins );

}

