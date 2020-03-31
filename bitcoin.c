#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define MAX_SIZE 50
#define MAX_SIZE1 100

#include "Tree.h"
#include "Wallet.h"
#include "Transaction.h"
#include "Hash_Table.h"


void Print_Menu(){

  printf("requestTransaction sender_ID receiver_ID amount [date] [time] \n");
  printf("requestTransactions sender_ID receiver_ID amount [date] [time]; \n" );
  printf("requestTransactions InputFile.txt\n" );
  printf("findEarnings walletID [time1] [date1] [time1] [date2]\n");
  printf("findPayments walletID [time1] [date1] [time1] [date2]\n");
  printf("walletStatus walletID\n");
  printf("bitCoinStatus bitCoinID\n");
  printf("traceCoin bitCoinID\n");
  printf("exit\n");

}



int main(int argc,char* argv[]){

  char* bitCoinBalancesFile;
  char* transactionsFile;
  int bitCoinValue;
  int senderHashtableNumOfEntries;
  int receiverHashtableNumOfEntries;
  int bucketsizeBytes;

  //Initializing command line arguments

  char* argm1=argv[1];
  if(strcmp(argm1,"-a")==0){

     bitCoinBalancesFile=argv[2];
  }
  char* argm3=argv[3];
  if(strcmp(argm3,"-t")==0){

    transactionsFile=argv[4];
  }
  char* arg5=argv[5];
  if(strcmp(arg5,"-v")==0){

    bitCoinValue=atoi(argv[6]);
  }
  char* arg7=argv[7];
  if(strcmp(arg7,"-h1")==0){

    senderHashtableNumOfEntries=atoi(argv[8]);
  }
  char* arg9=argv[9];
  if(strcmp(arg9,"-h2")==0){

    receiverHashtableNumOfEntries=atoi(argv[10]);
  }
  char* arg11=argv[11];
  if(strcmp(arg11,"-b")==0){

    bucketsizeBytes=atoi(argv[12]);
  }
  
  int RealBucketSize=bucketsizeBytes/sizeof(struct bucket_data); //Bucket_data is 16 bytes so to get the size of bucket array the bytes are divided by 16
  if(RealBucketSize==0){ //If a number less than 16 is given then the RealBucketSize is set to 1 in order to have at least one available spot
    RealBucketSize=1;
  }

  


  char ch;
  int failure=0;

  FILE *bf;
  bf = fopen(bitCoinBalancesFile,"r"); 

  if(bf==NULL){
    printf("Sorry file does not exist :/ \n");
  }

  struct wallet_list* wroot=NULL;
  struct bit_list* broot=NULL;
  int c=0;

  //Doing work for BitCoinBalancesFile
  printf("Processing BitCoinBalancesFile... \n");

    while (!feof(bf)){
          
      struct wallet temp;
      fscanf(bf,"%c",&ch);
      temp.ID[0]=ch;

      c=1;
      for(c;c<MAX_SIZE;c++){ //Getting the WalletID

        fscanf(bf,"%c",&ch);
        
        if(ch==' ' || ch=='\n'){
          temp.ID[c]='\0';        
          break;
        }

        temp.ID[c]=ch;
        
      }
      c=0;


      if(wroot!=NULL){
        struct wallet_list* stekei=wroot;
      while(stekei!=NULL){
        if(strcmp(temp.ID,stekei->wallie.ID)==0){
        
          printf("failure\n");
          failure=1;

          break;
        }
        stekei=stekei->next;
      }
      }
      assert(failure!=1); //If user already exists assert is used to close the program

      
      struct wallet_list* whold=wroot;

      if(wroot==NULL){
        wroot=new_wallet(temp);
        whold=wroot;
      }else{
        struct wallet_list* wtemp= wroot;
        
        wtemp=get_last_wallet(wtemp);
        struct wallet_list* new_node=new_wallet(temp);
        wtemp->next=new_node;
        whold=wtemp->next;
      }

      if(ch==' ' || ch!='\n'){ //getting the bitcoin ID 

        char bittempID[MAX_SIZE];

        int j=0;
        for(j;j<MAX_SIZE;j++){
          
          fscanf(bf,"%c",&ch);       

          if(ch==' ' || ch=='\n'){


            struct bit_list* bhold = broot;
      
            if(broot==NULL){

              broot=malloc(sizeof(struct bit_list));
              bittempID[j]='\0';
          
              broot->bp=newnode(bitCoinValue,bittempID,temp.ID);
              broot->bp->originaldata=bitCoinValue;
              broot->bp->isleft=0;
              broot->bp->isright=0;
              broot->bp->allspent=0;
              broot->bp->transp=NULL;
              broot->next=NULL;

              bhold=broot;


            }else{
              struct bit_list* btemp=broot;

              bittempID[j]='\0';
              struct bit_list* stekei=broot;
              while(stekei!=NULL){
              if(strcmp(bittempID,stekei->bp->ID)==0){

                
              printf("failure\n");
              failure=1;

              break;
              }
              stekei=stekei->next;
              }

              assert(failure!=1);
              
              btemp = get_last_bit(btemp);

                struct bit_list* bnew_node=malloc(sizeof(struct bit_list));
                bittempID[j]='\0';
                
                bnew_node->bp=newnode(bitCoinValue,bittempID,temp.ID);
                bnew_node->bp->originaldata=bitCoinValue;
                bnew_node->bp->isleft=0;
                bnew_node->bp->isright=0;
                bnew_node->bp->allspent=0;
                bnew_node->bp->transp=NULL;
                bnew_node->next=NULL;
                btemp->next=bnew_node;
                

                bhold=bnew_node;

            }


              if(whold->wallie.ulr==NULL){
                whold->wallie.ulr = malloc(sizeof(struct bit_list));
                whold->wallie.ulr->bp = bhold->bp;
                whold->wallie.ulr->next=NULL;

              }else{
                
                struct bit_list* temp= whold->wallie.ulr;
                
                temp = get_last_bit(temp);
                struct bit_list* new_node = malloc(sizeof(struct bit_list));
                new_node->bp = bhold->bp;
                new_node->next=NULL;
                temp->next=new_node;
    
              }

                          
            j=-1;
            if(ch==' '){
              continue;
            }else if(ch=='\n'){
              break;
            }
          }


          bittempID[j]=ch;

        }
      }else  if(ch=='\n'){
        continue;
      }


   }


   int i=0;

   //the following code takes care of some invalid users (i.e \n wallets)
    struct wallet_list* w1temp=wroot;
    struct wallet_list* previous= NULL;
    while(w1temp->next!=NULL && w1temp->wallie.ID[0]!='\n'){
      
      previous=w1temp;
      w1temp=w1temp->next;
    }

    if(w1temp->wallie.ID[0]=='\n'){

      if(previous==NULL){
      struct wallet_list* tnext=w1temp->next;
      free(w1temp);
      wroot=tnext;
    }else{
      struct wallet_list* tnext=w1temp->next;
      free(w1temp);
      previous->next=tnext;
      
    }

    }



    struct wallet_list* wtemp=wroot;
    calculate_sum(wtemp);


    struct bit_list* btemp=broot;
    



    fclose(bf);

    char cz;

    FILE *tf;
    tf = fopen(transactionsFile,"r"); 

    if(tf==NULL){
      printf("Sorry file does not exist :/ \n");
    
    }
    
    printf("Processing transactionsFile ... \n");

  int created=0;
  
  struct trans_list* troot=NULL;
  int ss,r,c1,amount;
  char samount[MAX_SIZE];
  int s1;
  char sday[3],smonth[3],syear[5];
  char sday2[3],smonth2[3],syear2[5];
  char shour[3],smins[3];
  char shour2[3],smins2[3];
  int prevday,prevmonth,prevyear;
  struct date prevdate;
  prevdate.day=0;
  prevdate.month=0;
  prevdate.year=0;

  struct time prevtime;
  int prevhour,prevmins;
  int sfailure=0;
  prevtime.hour=0;
  prevtime.mins=0;


  int day,month,year;
  int hour,mins;
  int more; 
  int isvalid=1;

  struct hash_table sender_hash;
  struct hash_table receiver_hash;


  while (!feof(tf)){ //Reading from transactionsFile

      isvalid=1;

      struct transaction temp;
      fscanf(tf,"%c",&cz);
      if(cz=='\n'){
        break;
      }
      temp.ID[0]=cz;

      c1=1;
      for(c1;c1<MAX_SIZE;c1++){ //getting transaction id 

        fscanf(tf,"%c",&cz);
        
        if(cz==' '){
          temp.ID[c1]='\0';       
          break;
        }

        temp.ID[c1]=cz;
        
      }
      c1=0;

     
      int failure=check_id(temp.ID,troot);
      if(failure==1){
        failure=0;
         while(cz!='\n'){
              fscanf(tf,"%c",&cz);
          
            }if(cz=='\n'){
              continue;

            }

      }



      fscanf(tf,"%c",&cz); //getting sender id 
      temp.sender_ID[0]=cz;   
      ss=1;
      for(ss;ss<MAX_SIZE;ss++){

        fscanf(tf,"%c",&cz);
        
        if(cz==' '){
          temp.sender_ID[ss]='\0';        
          break;
        }

        temp.sender_ID[ss]=cz;
            
        
      }
      ss=0;


      struct wallet_list* stekei=wroot;
      
      isvalid=check_userid(wroot,temp.sender_ID);
      if(isvalid==0){
        while(cz!='\n'){

          fscanf(tf,"%c",&cz);
          
          
        }if(cz=='\n'){
        continue;

        } 
      }
      

      fscanf(tf,"%c",&cz);  //getting receiver id 
      temp.receiver_ID[0]=cz;     
      r=1;
      for(r;r<MAX_SIZE;r++){

        fscanf(tf,"%c",&cz);
        
        if(cz==' '){
          temp.receiver_ID[r]='\0';       
          break;
        }

        temp.receiver_ID[r]=cz;
        
      }
      r=0;

     
      isvalid=check_userid(wroot,temp.receiver_ID);
      if(isvalid==0){
        while(cz!='\n'){

          fscanf(tf,"%c",&cz);
        
          
        }if(cz=='\n'){
        continue;

        } 
      }

      sfailure=is_same(temp.sender_ID,temp.receiver_ID);
      if(sfailure==1){
        sfailure=0;
         while(cz!='\n'){
              fscanf(tf,"%c",&cz);
          
            }if(cz=='\n'){
              continue;

            }

      }


      fscanf(tf,"%c",&cz); //getting the amount
      samount[0]=cz;      
      s1=1;
      for(s1;s1<MAX_SIZE;s1++){

        fscanf(tf,"%c",&cz);
        
        if(cz==' '){ 
          samount[s1]='\0';             
          break;
        }

        samount[s1]=cz;
        
      }
    
      s1=0;


      amount=atoi(samount);
 

      isvalid=check_amount(wroot,temp.sender_ID,amount);
      if(isvalid==0){
        while(cz!='\n'){
              fscanf(tf,"%c",&cz);
          
            }if(cz=='\n'){
              continue;

            }
      }

      temp.amount=amount;
      


      //getting date and time
      fscanf(tf,"%c",&cz);
      sday[0]=cz;
      fscanf(tf,"%c",&cz);
      sday[1]=cz;
      int day =atoi(sday);
      temp.tdate.day=day; 
      
      
      fscanf(tf,"%c",&cz);

      fscanf(tf,"%c",&cz);
      smonth[0]=cz;
      fscanf(tf,"%c",&cz);
      smonth[1]=cz;
      int month=atoi(smonth);
      temp.tdate.month=month;
    
      

      fscanf(tf,"%c",&cz);

      fscanf(tf,"%c",&cz);
      syear[0]=cz;
      fscanf(tf,"%c",&cz);
      syear[1]=cz;
      fscanf(tf,"%c",&cz);
      syear[2]=cz;
      fscanf(tf,"%c",&cz);
      syear[3]=cz;
      int year=atoi(syear);
      temp.tdate.year=year;
      

      
      fscanf(tf,"%c",&cz);

      fscanf(tf,"%c",&cz);
      shour[0]=cz;
      fscanf(tf,"%c",&cz);
      shour[1]=cz;
      int hour=atoi(shour);
      temp.ttime.hour=hour;
      
      

      fscanf(tf,"%c",&cz);      

      fscanf(tf,"%c",&cz);
      smins[0]=cz;
      fscanf(tf,"%c",&cz);
      smins[1]=cz;
      int mins=atoi(smins);
      temp.ttime.mins=mins;

      if(troot==NULL){
        prevdate.day=temp.tdate.day;
        prevdate.month=temp.tdate.month;
        prevdate.year=temp.tdate.year;
        prevtime.hour=temp.ttime.hour;
        prevtime.mins=temp.ttime.mins;
      }else{
        int dresult=check_dates(temp.tdate,prevdate);
        if(dresult==1){
          prevdate.day=temp.tdate.day;
          prevdate.month=temp.tdate.month;
          prevdate.year=temp.tdate.year;
          prevtime.hour=temp.ttime.hour;
          prevtime.mins=temp.ttime.mins;
        }
        if(dresult==0){
          while(cz!='\n'){
          fscanf(tf,"%c",&cz);
          
          
          }if(cz=='\n'){
          continue;

          }
        }
        if(dresult==2){
          int tresult=check_times(temp.ttime,prevtime);
          if(tresult==1){
            prevdate.day=temp.tdate.day;
            prevdate.month=temp.tdate.month;
            prevdate.year=temp.tdate.year;
            prevtime.hour=temp.ttime.hour;
            prevtime.mins=temp.ttime.mins;
          }
          if(tresult==0){
            while(cz!='\n'){
            fscanf(tf,"%c",&cz);
          
          
            }if(cz=='\n'){
            continue;

            }   
          }
        }
      }
      
      //everything is valid. add the transaction at the end of the list
      struct trans_list* thold=NULL;
      if(troot==NULL){
        troot=malloc(sizeof(struct trans_list));
        troot->trans=temp;
        troot->next=NULL;
        thold=troot;
      }else{
        struct trans_list* trtemp=troot;
        trtemp=get_last_trans(trtemp);
        struct trans_list* troo=malloc(sizeof(struct trans_list));
        troo->trans=temp;
        troo->next=NULL;
        trtemp->next=troo;
        thold=trtemp->next;
      }
      

      int remaining=0;
      struct bit_list* templist=NULL;
      struct wallet_list* wtempt=wroot;
      struct tree_node* hold=NULL;

      int more=how_many(wtempt,thold);  //updating the existing data structures. Please see Wallet.c and Tree.c files for the code of each one

      wtempt=wroot;
      if(more==0){
        hold=get_bitcoin(wtempt,thold);
      }else if(more==1){
        templist=get_bitcoin_list(wtempt,thold);

      }

      if(more==0){
        break_bitcoin(hold,thold);
      }else if(more==1){

        break_bitcoin_list(templist,thold);
      }

      if(more==0){
        wtempt=wroot;
        update_sender_one(wtempt,thold,hold);
        wtempt=wroot;
        update_receiver_one(wtempt,thold,hold);
      }else if(more==1){
        wtempt=wroot;
        update_sender_many(wtempt,thold,templist);
        wtempt=wroot;
        update_receiver_many(wtempt,thold,templist);
      } 

      


      if(created==0){ //creating the hash tables

        created=1;
        

        sender_hash.hash_array=malloc(senderHashtableNumOfEntries * sizeof(struct bucket_list*));
        receiver_hash.hash_array=malloc(receiverHashtableNumOfEntries * sizeof(struct bucket_list*));

        int i=0;
        for(i;i<senderHashtableNumOfEntries;i++){
          sender_hash.hash_array[i]=NULL;
        }

        int j=0;
        for(j;j<receiverHashtableNumOfEntries;j++){
          receiver_hash.hash_array[j]=NULL;
        }

      }



      int key=hash_func(thold->trans.sender_ID,senderHashtableNumOfEntries); //doing work for the sender

      if(sender_hash.hash_array[key]==NULL){

        sender_hash.hash_array[key]=malloc(sizeof(struct bucket_list)); 

        struct bucket_list* buckettemp=sender_hash.hash_array[key];
        add_first(buckettemp,thold,RealBucketSize,0);

      }else{

        struct bucket_list* buckettemp = sender_hash.hash_array[key];
        struct trans_list_hash* breturn=search(buckettemp,thold->trans.sender_ID,RealBucketSize);
        struct trans_list_hash* argument=breturn;
       
        if(breturn==NULL){
          struct bucket_list* buckettemp=sender_hash.hash_array[key];
          add_free(buckettemp,thold,RealBucketSize,0);

        }else{
          add_existing(argument,thold);
        }
        
      }


      int key1=hash_func(thold->trans.receiver_ID,receiverHashtableNumOfEntries); //doing work for the receiver

      if(receiver_hash.hash_array[key1]==NULL){


        receiver_hash.hash_array[key1]=malloc(sizeof(struct bucket_list)); 
        struct bucket_list* buckettemp=receiver_hash.hash_array[key1];
        add_first(buckettemp,thold,RealBucketSize,1);
        


      }else{

        struct bucket_list* buckettemp = receiver_hash.hash_array[key1];
        struct trans_list_hash* breturn=search(buckettemp,thold->trans.receiver_ID,RealBucketSize);
        struct trans_list_hash* argument=breturn;
       
        if(breturn==NULL){
          struct bucket_list* buckettemp=receiver_hash.hash_array[key1];
          add_free(buckettemp,thold,RealBucketSize,1);

        }else{
          add_existing(argument,thold);
        }

      }



      struct bit_list* btemp2=templist; //deleting the temp list
      struct bit_list* bcurr=btemp2;
      struct bit_list* bnext;

      while(bcurr !=NULL){

        bnext=bcurr->next;
        free(bcurr);

        bcurr=bnext;

      }

      btemp2=NULL;

      templist=NULL;

      fscanf(tf,"%c",&cz);
      continue;

    }


    //creating a new id for the transactions from the command menu
    char transidd[15]; //we get a number that is not already there and we increment it at every new transaction
    srand(time(0));
    int x = rand();
    while(1){
      if(x>999999999999999){
        x = rand();
        continue;
      }else{
        break;
      }
    }

    
    sprintf(transidd, "%d", x);



    struct trans_list* tfind=troot;
    while(tfind!=NULL){
      if(strcmp(transidd,tfind->trans.ID)==0){
        
        x = rand();
        printf("%d\n",x );
        sprintf(transidd, "%d", x);
        tfind=troot;
        continue;
      }
      tfind=tfind->next;

    }

    int longest_id = x;

    struct bit_list* brtemp=broot;
   

     fclose(tf);


     char *line = NULL;
     size_t line_size;

     char *transline = NULL;
     size_t transline_size;

     char transid[15];
     char* sender=NULL;
     char* receiver=NULL;
     char* tamount=NULL;
     char* walletpay=NULL;
     char* walletearn=NULL;
     char* walletsuma=NULL;
     char* bitcoinstat=NULL;
     char* time1=NULL;
     char* time2=NULL;
     char* date1=NULL;
     char* date2=NULL;
     char* tracecoin=NULL;
     char* inputfile=NULL;
     int ufailure=0;
     struct time starttime;
     struct time endtime;
     struct date startdate;
     struct date enddate;
     char* arg1=NULL;
     char* arg2=NULL;
     char* arg3=NULL;
     char* arg4=NULL;

     //Command menu

     printf("Welcome user to the command menu!\n");
     printf("You are free to type any of the following commands\n");
     printf("Note: Arguments in brackets are optional \n");
     printf("Note 2: For the requestTransactions command please use semicolon (;) for each command. If you wish to exit type 0\n");
     printf("\n");
     Print_Menu();


     while (getline(&line,&line_size,stdin) != -1){
      
      char *command = strtok(line," ");
      if(strcmp(command,"requestTransaction")==0){ //requestTransaction does similar work as explained above
        while(command!=NULL){
            
            command = strtok(NULL, " ");

            if(sender==NULL){
              sender=command;
              continue;
            }
            if(receiver==NULL){
              receiver=command;
              continue; 
            }
            if(tamount==NULL){
              tamount=command;
              continue; 
            }
            if(date1==NULL){
              date1=command;
              continue; 
            }
            if(time1==NULL){
              time1=command;
              continue; 
            }     

          }

          if(sender==NULL || receiver==NULL || tamount==NULL){

            printf("Invalid input :/ \n");
            printf("\n");
            Print_Menu();
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
            continue;
          }
          if((date1!=NULL && time1==NULL )|| (time1!=NULL && date1==NULL)){

            printf("Invalid input :/ \n");
            printf("\n");
            Print_Menu();
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
            continue; 
          }
          
          struct transaction tnew;
          isvalid=1;
          sfailure=0;

          isvalid=check_userid(wroot,sender);
          if(isvalid==0){
            printf("User does not exist :/ \n"); 
            printf("\n");
            Print_Menu();
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
            continue;  
          }

          strcpy(tnew.sender_ID,sender);
          isvalid=check_userid(wroot,receiver);

          if(isvalid==0){
            printf("User does not exist :/ \n"); 
            printf("\n");
            Print_Menu();
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
            continue;  
          }
          strcpy(tnew.receiver_ID,receiver);
          sfailure=is_same(sender,receiver);
          if(sfailure==1){
            printf("Users can't be the same :/ \n"); 
            printf("\n");
            Print_Menu();
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
            continue; 
          }

          int newamount=atoi(tamount);

          isvalid=check_amount(wroot,sender,newamount);
          if(isvalid==0){
            printf("Not enough money :/ \n"); 
            printf("\n");
            Print_Menu();
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
            continue; 
          }

          tnew.amount=newamount;



          if(date1==NULL && time1==NULL){
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
             
             tnew.tdate.day=tm.tm_mday;
             tnew.tdate.month=tm.tm_mon + 1;
             tnew.tdate.year=tm.tm_year + 1900;
             tnew.ttime.hour=tm.tm_hour;
             tnew.ttime.mins=tm.tm_min;


          }else if(date1!=NULL && time1!=NULL){


          sday[0]=date1[0];
          sday[1]=date1[1];
          smonth[0]=date1[3];
          smonth[1]=date1[4];
          syear[0]=date1[6];
          syear[1]=date1[7];
          syear[2]=date1[8];
          syear[3]=date1[9];
          tnew.tdate.day=atoi(sday);
          tnew.tdate.month=atoi(smonth);
          tnew.tdate.year=atoi(syear);
          shour[0]=time1[0];
          shour[1]=time1[1];
          smins[0]=time1[3];
          smins[1]=time1[4];
          tnew.ttime.hour=atoi(shour);
          tnew.ttime.mins=atoi(smins);

          }

          int dresult=check_dates(tnew.tdate,prevdate);
          if(dresult==1){
          prevdate.day=tnew.tdate.day;
          prevdate.month=tnew.tdate.month;
          prevdate.year=tnew.tdate.year;
          prevtime.hour=tnew.ttime.hour;
          prevtime.mins=tnew.ttime.mins;
        }
        if(dresult==0){
          printf("Invalid date :/ \n"); 
          printf("\n");
            Print_Menu();
          sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
          continue; 
        }
        if(dresult==2){
          int tresult=check_times(tnew.ttime,prevtime);
          if(tresult==1){
            prevdate.day=tnew.tdate.day;
            prevdate.month=tnew.tdate.month;
            prevdate.year=tnew.tdate.year;
            prevtime.hour=tnew.ttime.hour;
            prevtime.mins=tnew.ttime.mins;
          }
          if(tresult==0){
            printf("Invalid date :/ \n");
            printf("\n");
            Print_Menu();
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL; 
            continue;   
          }
        }

          longest_id=longest_id+1;
          sprintf(transid, "%d", longest_id);
          
          strcpy(tnew.ID,transid);
          
          struct trans_list* thold;
          struct trans_list* trtemp=troot;
          trtemp=get_last_trans(trtemp);
          struct trans_list* troo=malloc(sizeof(struct trans_list));
          troo->trans=tnew;
          troo->next=NULL;
          trtemp->next=troo;
          thold=trtemp->next;


          int remaining=0;
      struct bit_list* templist=NULL;
      struct wallet_list* wtempt=wroot;
      struct tree_node* hold=NULL;

      int more=how_many(wtempt,thold);

      wtempt=wroot;
      if(more==0){
        hold=get_bitcoin(wtempt,thold);
      }else if(more==1){
        templist=get_bitcoin_list(wtempt,thold);
      }

      if(more==0){
        break_bitcoin(hold,thold);
      }else if(more==1){
        break_bitcoin_list(templist,thold);
      }

      if(more==0){
        wtempt=wroot;
        update_sender_one(wtempt,thold,hold);
        wtempt=wroot;
        update_receiver_one(wtempt,thold,hold);
      }else if(more==1){
        wtempt=wroot;
        update_sender_many(wtempt,thold,templist);
        wtempt=wroot;
        update_receiver_many(wtempt,thold,templist);
      }


      int key=hash_func(thold->trans.sender_ID,senderHashtableNumOfEntries);


      if(sender_hash.hash_array[key]==NULL){

        sender_hash.hash_array[key]=malloc(sizeof(struct bucket_list)); 

        struct bucket_list* buckettemp=sender_hash.hash_array[key];
        add_first(buckettemp,thold,RealBucketSize,0);

      }else{

        struct bucket_list* buckettemp = sender_hash.hash_array[key];
        struct trans_list_hash* breturn=search(buckettemp,thold->trans.sender_ID,RealBucketSize);
        struct trans_list_hash* argument=breturn;
       
        if(breturn==NULL){
          struct bucket_list* buckettemp=sender_hash.hash_array[key];
          add_free(buckettemp,thold,RealBucketSize,0);

        }else{
          add_existing(argument,thold);
        }
        
      }

      int key1=hash_func(thold->trans.receiver_ID,receiverHashtableNumOfEntries);

      if(receiver_hash.hash_array[key1]==NULL){


        receiver_hash.hash_array[key1]=malloc(sizeof(struct bucket_list)); 
        struct bucket_list* buckettemp=receiver_hash.hash_array[key1];
        add_first(buckettemp,thold,RealBucketSize,1);
        


      }else{

        struct bucket_list* buckettemp = receiver_hash.hash_array[key1];
        struct trans_list_hash* breturn=search(buckettemp,thold->trans.receiver_ID,RealBucketSize);
        struct trans_list_hash* argument=breturn;
       
        if(breturn==NULL){
          struct bucket_list* buckettemp=receiver_hash.hash_array[key1];
          add_free(buckettemp,thold,RealBucketSize,1);

        }else{
          add_existing(argument,thold);
        }

      }

      print_transaction(thold->trans);
      printf("Transaction Complete \n");

      printf("\n");
            Print_Menu();


        struct bit_list* btemp2=templist;
      struct bit_list* bcurr=btemp2;
      struct bit_list* bnext;

      while(bcurr !=NULL){
        //free(bcurr->bp);
        bnext=bcurr->next;
        free(bcurr);

        bcurr=bnext;

      }

      btemp2=NULL;

      templist=NULL;


          
          sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;



          continue;

      }
      if(strcmp(command,"requestTransactions")==0){
        command = strtok(NULL, " ");
        
        if(strcmp(command,"InputFile.txt\n")==0){ //reading transactions from InputFile. Similar code for the starting file


          char ci;

          FILE *inf;
          inf = fopen("InputFile.txt","r");

        if(inf==NULL){
          printf("Sorry file does not exist :/ \n");
          printf("\n");
            Print_Menu();
          }

          int nodates=0;

    while (!feof(inf)){


      isvalid=1;

      struct transaction temp;
        

      fscanf(inf,"%c",&ci);
      temp.sender_ID[0]=ci;   
      ss=1;
      for(ss;ss<MAX_SIZE;ss++){

        fscanf(inf,"%c",&ci);
        
        if(ci==' '){
          temp.sender_ID[ss]='\0';        
          break;
        }

        temp.sender_ID[ss]=ci;
            
        
      }
      ss=0;


      struct wallet_list* stekei=wroot;
      
      isvalid=check_userid(wroot,temp.sender_ID);
      if(isvalid==0){
        while(ci!='\n'){

          fscanf(tf,"%c",&cz);
          
          
        }if(ci=='\n'){
        continue;

        } 
      }
      

      fscanf(inf,"%c",&ci);
      temp.receiver_ID[0]=ci;     
      r=1;
      for(r;r<MAX_SIZE;r++){

        fscanf(inf,"%c",&ci);
        
        if(ci==' '){
          temp.receiver_ID[r]='\0';       
          break;
        }

        temp.receiver_ID[r]=ci;
        
      }
      r=0;

      
      isvalid=check_userid(wroot,temp.receiver_ID);
      if(isvalid==0){
        while(ci!='\n'){

          fscanf(inf,"%c",&ci);
          
          
        }if(ci=='\n'){
        continue;

        } 
      }

      sfailure=is_same(temp.sender_ID,temp.receiver_ID);
      if(sfailure==1){
        sfailure=0;
         while(ci!='\n'){
              fscanf(inf,"%c",&ci);
          
            }if(ci=='\n'){
              continue;

            }

      }


      fscanf(inf,"%c",&ci);
      samount[0]=ci;      
      s1=1;
      for(s1;s1<MAX_SIZE;s1++){

        fscanf(inf,"%c",&ci);

        if(ci=='\n'){ 
          printf("semicolon missing\n");
          isvalid=0;
          break;
        }      

        if(ci==';'){ 
          samount[s1]='\0';
          nodates=1;             
          break;
        }
        
        if(ci==' '){ 
          samount[s1]='\0';             
          break;
        }

        samount[s1]=ci;
        
      }
    
      s1=0;

      if(isvalid==0){
        while(ci!='\n'){

          fscanf(inf,"%c",&ci);
          
          
        }if(ci=='\n'){
        continue;

        } 
      }



      amount=atoi(samount);
      

      isvalid=check_amount(wroot,temp.sender_ID,amount);
      if(isvalid==0){
        while(ci!='\n'){
              fscanf(inf,"%c",&ci);
          
            }if(ci=='\n'){
              continue;

            }
      }

      temp.amount=amount;

      if(nodates==1){
        time_t t = time(NULL);
            struct tm tm = *localtime(&t);
             
             temp.tdate.day=tm.tm_mday;
             temp.tdate.month=tm.tm_mon + 1;
             temp.tdate.year=tm.tm_year + 1900;
             temp.ttime.hour=tm.tm_hour;
             temp.ttime.mins=tm.tm_min;
      }
      
      if(nodates==0){


      fscanf(inf,"%c",&ci);
      sday[0]=ci;
      fscanf(inf,"%c",&ci);
      sday[1]=ci;
      int day =atoi(sday);
      temp.tdate.day=day; 
      
      
      fscanf(inf,"%c",&ci);

      fscanf(inf,"%c",&ci);
      smonth[0]=ci;
      fscanf(inf,"%c",&ci);
      smonth[1]=ci;
      int month=atoi(smonth);
      temp.tdate.month=month;
    
      

      fscanf(inf,"%c",&ci);

      fscanf(inf,"%c",&ci);
      syear[0]=ci;
      fscanf(inf,"%c",&ci);
      syear[1]=ci;
      fscanf(inf,"%c",&ci);
      syear[2]=ci;
      fscanf(inf,"%c",&ci);
      syear[3]=ci;
      int year=atoi(syear);
      temp.tdate.year=year;
      

      
      fscanf(inf,"%c",&ci);

      fscanf(inf,"%c",&ci);
      shour[0]=ci;
      fscanf(inf,"%c",&ci);
      shour[1]=ci;
      int hour=atoi(shour);
      temp.ttime.hour=hour;
      
      

      fscanf(inf,"%c",&ci);      

      fscanf(inf,"%c",&ci);
      smins[0]=ci;
      fscanf(inf,"%c",&ci);
      smins[1]=ci;
      int mins=atoi(smins);
      temp.ttime.mins=mins;

      fscanf(inf,"%c",&ci);
      if(ci!=';'){
          printf("semicolon missing\n");
          isvalid=0;

      }

    }

    if(isvalid==0){
        while(ci!='\n'){

          fscanf(inf,"%c",&ci);
          
          //yas=0;
          
        }if(ci=='\n'){
        continue;

        } 
      }



      if(troot==NULL){
        prevdate.day=temp.tdate.day;
        prevdate.month=temp.tdate.month;
        prevdate.year=temp.tdate.year;
        prevtime.hour=temp.ttime.hour;
        prevtime.mins=temp.ttime.mins;
      }else{

        int dresult=check_dates(temp.tdate,prevdate);
        if(dresult==1){
          prevdate.day=temp.tdate.day;
          prevdate.month=temp.tdate.month;
          prevdate.year=temp.tdate.year;
          prevtime.hour=temp.ttime.hour;
          prevtime.mins=temp.ttime.mins;
        }
        if(dresult==0){
          nodates=0;
          while(ci!='\n'){

          fscanf(inf,"%c",&ci);
          
          
          }if(ci=='\n'){
          continue;

          }
        }
        if(dresult==2){
          int tresult=check_times(temp.ttime,prevtime);
          if(tresult==1){
            prevdate.day=temp.tdate.day;
            prevdate.month=temp.tdate.month;
            prevdate.year=temp.tdate.year;
            prevtime.hour=temp.ttime.hour;
            prevtime.mins=temp.ttime.mins;
          }
          if(tresult==0){
            nodates=0;
            while(ci!='\n'){
            
            fscanf(inf,"%c",&ci);
          
          
            }if(ci=='\n'){
            continue;

            }   
          }
        }
      
      }

          longest_id=longest_id+1;
          sprintf(transid, "%d", longest_id);
          
          strcpy(temp.ID,transid);


      
      struct trans_list* thold=NULL;
      if(troot==NULL){
        troot=malloc(sizeof(struct trans_list));
        troot->trans=temp;
        troot->next=NULL;
        thold=troot;
      }else{
        struct trans_list* trtemp=troot;
        trtemp=get_last_trans(trtemp);
        struct trans_list* troo=malloc(sizeof(struct trans_list));
        troo->trans=temp;
        troo->next=NULL;
        trtemp->next=troo;
        thold=trtemp->next;
      }


      int remaining=0;
      struct bit_list* templist=NULL;
      struct wallet_list* wtempt=wroot;
      struct tree_node* hold=NULL;

      int more=how_many(wtempt,thold);

      wtempt=wroot;
      if(more==0){
        hold=get_bitcoin(wtempt,thold);
      }else if(more==1){
        templist=get_bitcoin_list(wtempt,thold);
      }

      if(more==0){
        break_bitcoin(hold,thold);
      }else if(more==1){
        break_bitcoin_list(templist,thold);
      }

      if(more==0){
        wtempt=wroot;
        update_sender_one(wtempt,thold,hold);
        wtempt=wroot;
        update_receiver_one(wtempt,thold,hold);
      }else if(more==1){
        wtempt=wroot;
        update_sender_many(wtempt,thold,templist);
        wtempt=wroot;
        update_receiver_many(wtempt,thold,templist);
      } 

      

      int key=hash_func(thold->trans.sender_ID,senderHashtableNumOfEntries);

      if(sender_hash.hash_array[key]==NULL){

        sender_hash.hash_array[key]=malloc(sizeof(struct bucket_list)); 

        struct bucket_list* buckettemp=sender_hash.hash_array[key];
        add_first(buckettemp,thold,RealBucketSize,0);

      }else{

        struct bucket_list* buckettemp = sender_hash.hash_array[key];
        struct trans_list_hash* breturn=search(buckettemp,thold->trans.sender_ID,RealBucketSize);
        struct trans_list_hash* argument=breturn;
       
        if(breturn==NULL){
          struct bucket_list* buckettemp=sender_hash.hash_array[key];
          add_free(buckettemp,thold,RealBucketSize,0);

        }else{
          add_existing(argument,thold);
        }
        
      }


      int key1=hash_func(thold->trans.receiver_ID,receiverHashtableNumOfEntries);

      if(receiver_hash.hash_array[key1]==NULL){


        receiver_hash.hash_array[key1]=malloc(sizeof(struct bucket_list)); 
        struct bucket_list* buckettemp=receiver_hash.hash_array[key1];
        add_first(buckettemp,thold,RealBucketSize,1);
        


      }else{

        struct bucket_list* buckettemp = receiver_hash.hash_array[key1];
        struct trans_list_hash* breturn=search(buckettemp,thold->trans.receiver_ID,RealBucketSize);
        struct trans_list_hash* argument=breturn;
       
        if(breturn==NULL){
          struct bucket_list* buckettemp=receiver_hash.hash_array[key1];
          add_free(buckettemp,thold,RealBucketSize,1);

        }else{
          add_existing(argument,thold);
        }

      }

      print_transaction(thold->trans);
      printf("Transaction Complete \n");


      struct bit_list* btemp2=templist;
      struct bit_list* bcurr=btemp2;
      struct bit_list* bnext;

      while(bcurr !=NULL){
        //free(bcurr->bp);
        bnext=bcurr->next;
        free(bcurr);

        bcurr=bnext;

      }

      btemp2=NULL;

      templist=NULL;

      nodates=0;

      fscanf(inf,"%c",&ci);
      continue;

    }



    fclose(inf);

    printf("\n");
            Print_Menu();


          continue;

        }else{ //reading transactions from stdin

            if(sender==NULL){
              sender=command;
            }
            while(command!=NULL){
            
            command = strtok(NULL, " ");
            if(receiver==NULL){
              receiver=command;
              continue; 
            }
            if(tamount==NULL){
              tamount=command;
              continue; 
            }
            if(date1==NULL){
              date1=command;
              continue; 
            }
            if(time1==NULL){
              time1=command;
              continue; 
            }

          }

          if(sender==NULL || receiver==NULL || tamount==NULL){

            printf("Invalid input :/ \n");
            printf("\n");
            Print_Menu();
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
            continue;
          }
          if((date1!=NULL && time1==NULL )|| (time1!=NULL && date1==NULL)){

            printf("Invalid input :/ \n");
            printf("\n");
            Print_Menu();
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
            continue; 
          }
          
          struct transaction tnew;
          isvalid=1;
          sfailure=0;

          isvalid=check_userid(wroot,sender);
          if(isvalid==0){
            printf("User does not exist :/ \n"); 
            printf("\n");
            Print_Menu();
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
            continue;  
          }
          strcpy(tnew.sender_ID,sender);
          isvalid=check_userid(wroot,receiver);
          if(isvalid==0){
            printf("User does not exist :/ \n"); 
            printf("\n");
            Print_Menu();
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
            continue;  
          }
          strcpy(tnew.receiver_ID,receiver);
          sfailure=is_same(sender,receiver);
          if(sfailure==1){
            printf("Users can't be the same :/ \n"); 
            printf("\n");
            Print_Menu();
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
            continue; 
          }


          int newamount=atoi(tamount);

          isvalid=check_amount(wroot,sender,newamount);
          if(isvalid==0){
            printf("Not enough money :/ \n"); 
            printf("\n");
            Print_Menu();
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
            continue; 
          }

          tnew.amount=newamount;



          if(date1==NULL && time1==NULL){
            //printf("it is %c\n",tamount[(strlen(tamount) -1 )] );
            if(tamount[(strlen(tamount) -2 )] != ';' ){
              printf("Please type semicolon too :/ \n"); 
              printf("\n");
            Print_Menu();
              sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
              continue; 

            }


            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
             
             tnew.tdate.day=tm.tm_mday;
             tnew.tdate.month=tm.tm_mon + 1;
             tnew.tdate.year=tm.tm_year + 1900;
             tnew.ttime.hour=tm.tm_hour;
             tnew.ttime.mins=tm.tm_min;


          }else if(date1!=NULL && time1!=NULL){
            if(time1[(strlen(time1) -2 )] != ';' ){
              printf("Please type semicolon too :/ \n"); 
              printf("\n");
            Print_Menu();
              sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
              continue; 

            }


          sday[0]=date1[0];
          sday[1]=date1[1];
          smonth[0]=date1[3];
          smonth[1]=date1[4];
          syear[0]=date1[6];
          syear[1]=date1[7];
          syear[2]=date1[8];
          syear[3]=date1[9];
          tnew.tdate.day=atoi(sday);
          tnew.tdate.month=atoi(smonth);
          tnew.tdate.year=atoi(syear);
          shour[0]=time1[0];
          shour[1]=time1[1];
          smins[0]=time1[3];
          smins[1]=time1[4];
          tnew.ttime.hour=atoi(shour);
          tnew.ttime.mins=atoi(smins);

          }

          int dresult=check_dates(tnew.tdate,prevdate);
          if(dresult==1){
          prevdate.day=tnew.tdate.day;
          prevdate.month=tnew.tdate.month;
          prevdate.year=tnew.tdate.year;
          prevtime.hour=tnew.ttime.hour;
          prevtime.mins=tnew.ttime.mins;
        }
        if(dresult==0){
          printf("Invalid date :/ \n"); 
          printf("\n");
            Print_Menu();
          sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
          continue; 
        }
        if(dresult==2){
          int tresult=check_times(tnew.ttime,prevtime);
          if(tresult==1){
            prevdate.day=tnew.tdate.day;
            prevdate.month=tnew.tdate.month;
            prevdate.year=tnew.tdate.year;
            prevtime.hour=tnew.ttime.hour;
            prevtime.mins=tnew.ttime.mins;
          }
          if(tresult==0){
            printf("Invalid date :/ \n"); 
            printf("\n");
            Print_Menu();
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
            continue;   
          }
        }

          longest_id=longest_id+1;
          sprintf(transid, "%d", longest_id);
          
          strcpy(tnew.ID,transid);
          
          struct trans_list* thold;
          struct trans_list* trtemp=troot;
          trtemp=get_last_trans(trtemp);
          struct trans_list* troo=malloc(sizeof(struct trans_list));
          troo->trans=tnew;
          troo->next=NULL;
          trtemp->next=troo;
          thold=trtemp->next;



          int remaining=0;
      struct bit_list* templist=NULL;
      struct wallet_list* wtempt=wroot;
      struct tree_node* hold=NULL;

      int more=how_many(wtempt,thold);

      wtempt=wroot;
      if(more==0){
        hold=get_bitcoin(wtempt,thold);
      }else if(more==1){
        templist=get_bitcoin_list(wtempt,thold);
      }

      if(more==0){
        break_bitcoin(hold,thold);
      }else if(more==1){
        break_bitcoin_list(templist,thold);
      }

      if(more==0){
        wtempt=wroot;
        update_sender_one(wtempt,thold,hold);
        wtempt=wroot;
        update_receiver_one(wtempt,thold,hold);
      }else if(more==1){
        wtempt=wroot;
        update_sender_many(wtempt,thold,templist);
        wtempt=wroot;
        update_receiver_many(wtempt,thold,templist);
      }


      int key=hash_func(thold->trans.sender_ID,senderHashtableNumOfEntries);


      if(sender_hash.hash_array[key]==NULL){

        sender_hash.hash_array[key]=malloc(sizeof(struct bucket_list)); 

        struct bucket_list* buckettemp=sender_hash.hash_array[key];
        add_first(buckettemp,thold,RealBucketSize,0);

      }else{

        struct bucket_list* buckettemp = sender_hash.hash_array[key];
        struct trans_list_hash* breturn=search(buckettemp,thold->trans.sender_ID,RealBucketSize);
        struct trans_list_hash* argument=breturn;
       
        if(breturn==NULL){
          struct bucket_list* buckettemp=sender_hash.hash_array[key];
          add_free(buckettemp,thold,RealBucketSize,0);

        }else{
          add_existing(argument,thold);
        }
        
      }

      int key1=hash_func(thold->trans.receiver_ID,receiverHashtableNumOfEntries);

      if(receiver_hash.hash_array[key1]==NULL){


        receiver_hash.hash_array[key1]=malloc(sizeof(struct bucket_list)); 
        struct bucket_list* buckettemp=receiver_hash.hash_array[key1];
        add_first(buckettemp,thold,RealBucketSize,1);
        


      }else{

        struct bucket_list* buckettemp = receiver_hash.hash_array[key1];
        struct trans_list_hash* breturn=search(buckettemp,thold->trans.receiver_ID,RealBucketSize);
        struct trans_list_hash* argument=breturn;
       
        if(breturn==NULL){
          struct bucket_list* buckettemp=receiver_hash.hash_array[key1];
          add_free(buckettemp,thold,RealBucketSize,1);

        }else{
          add_existing(argument,thold);
        }

      }

      print_transaction(thold->trans);
      printf("Transaction Complete \n");


        struct bit_list* btemp2=templist;
      struct bit_list* bcurr=btemp2;
      struct bit_list* bnext;

      while(bcurr !=NULL){
        //free(bcurr->bp);
        bnext=bcurr->next;
        free(bcurr);

        bcurr=bnext;

      }

      btemp2=NULL;

      templist=NULL;

          
          sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;

          int exited=0;
          while (getline(&transline,&transline_size,stdin) != -1){ //loop that reads more transactions until 0 is typed
            char *transcommand = strtok(transline," ");
            if(strcmp(transline,"0\n")==0){
              printf("Exiting the requestTransactions command! \n");
              transcommand=NULL;
              exited=1;
              break;
            }
            if(exited==1){
              exited=0;
              break;
            }
             if(sender==NULL){
              sender=transcommand;
            }
            while(transcommand!=NULL){
            
            transcommand = strtok(NULL, " ");

          
            if(receiver==NULL){
              receiver=transcommand;
              continue; 
            }
            if(tamount==NULL){
              tamount=transcommand;
              continue; 
            }
            if(date1==NULL){
              date1=transcommand;
              continue; 
            }
            if(time1==NULL){
              time1=transcommand;
              continue; 
            }     

          }

          if(sender==NULL || receiver==NULL || tamount==NULL){

            printf("Invalid input :/ \n");
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
            continue;
          }
          if((date1!=NULL && time1==NULL )|| (time1!=NULL && date1==NULL)){

            printf("Invalid input :/ \n");
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
            continue; 
          }
          
          struct transaction tnew;
          isvalid=1;
          sfailure=0;

          isvalid=check_userid(wroot,sender);
          if(isvalid==0){
            printf("User does not exist :/ \n"); 
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
            continue;  
          }
          strcpy(tnew.sender_ID,sender);
          isvalid=check_userid(wroot,receiver);
          if(isvalid==0){
            printf("User does not exist :/ \n"); 
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
            continue;  
          }
          strcpy(tnew.receiver_ID,receiver);
          sfailure=is_same(sender,receiver);
          if(sfailure==1){
            printf("Users can't be the same :/ \n"); 
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
            continue; 
          }

          int newamount=atoi(tamount);

          isvalid=check_amount(wroot,sender,newamount);
          if(isvalid==0){
            printf("Not enough money :/ \n"); 
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
            continue; 
          }

          tnew.amount=newamount;



          if(date1==NULL && time1==NULL){
            if(tamount[(strlen(tamount) -2 )] != ';' ){
              printf("Please type semicolon too :/ \n"); 
              sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
              continue; 

            }

            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
             
             tnew.tdate.day=tm.tm_mday;
             tnew.tdate.month=tm.tm_mon + 1;
             tnew.tdate.year=tm.tm_year + 1900;
             tnew.ttime.hour=tm.tm_hour;
             tnew.ttime.mins=tm.tm_min;


          }else if(date1!=NULL && time1!=NULL){

            if(time1[(strlen(time1) -2 )] != ';' ){
              printf("Please type semicolon too :/ \n"); 
              sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
              continue; 

            }


          sday[0]=date1[0];
          sday[1]=date1[1];
          smonth[0]=date1[3];
          smonth[1]=date1[4];
          syear[0]=date1[6];
          syear[1]=date1[7];
          syear[2]=date1[8];
          syear[3]=date1[9];
          tnew.tdate.day=atoi(sday);
          tnew.tdate.month=atoi(smonth);
          tnew.tdate.year=atoi(syear);
          shour[0]=time1[0];
          shour[1]=time1[1];
          smins[0]=time1[3];
          smins[1]=time1[4];
          tnew.ttime.hour=atoi(shour);
          tnew.ttime.mins=atoi(smins);

          }

          int dresult=check_dates(tnew.tdate,prevdate);
          if(dresult==1){
          prevdate.day=tnew.tdate.day;
          prevdate.month=tnew.tdate.month;
          prevdate.year=tnew.tdate.year;
          prevtime.hour=tnew.ttime.hour;
          prevtime.mins=tnew.ttime.mins;
        }
        if(dresult==0){
          printf("Invalid date :/ \n"); 
          sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;
          continue; 
        }
        if(dresult==2){
          int tresult=check_times(tnew.ttime,prevtime);
          if(tresult==1){
            prevdate.day=tnew.tdate.day;
            prevdate.month=tnew.tdate.month;
            prevdate.year=tnew.tdate.year;
            prevtime.hour=tnew.ttime.hour;
            prevtime.mins=tnew.ttime.mins;
          }
          if(tresult==0){
            printf("Invalid date :/ \n");
            sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL; 
            continue;   
          }
        }

          longest_id=longest_id+1;
          sprintf(transid, "%d", longest_id);
          
          strcpy(tnew.ID,transid);
          
          struct trans_list* thold;
          struct trans_list* trtemp=troot;
          trtemp=get_last_trans(trtemp);
          struct trans_list* troo=malloc(sizeof(struct trans_list));
          troo->trans=tnew;
          troo->next=NULL;
          trtemp->next=troo;
          thold=trtemp->next;


          int remaining=0;
      struct bit_list* templist=NULL;
      struct wallet_list* wtempt=wroot;
      struct tree_node* hold=NULL;

      int more=how_many(wtempt,thold);

      wtempt=wroot;
      if(more==0){
        hold=get_bitcoin(wtempt,thold);
      }else if(more==1){
        templist=get_bitcoin_list(wtempt,thold);
      }

      if(more==0){
        break_bitcoin(hold,thold);
      }else if(more==1){
        break_bitcoin_list(templist,thold);
      }

      if(more==0){
        wtempt=wroot;
        update_sender_one(wtempt,thold,hold);
        wtempt=wroot;
        update_receiver_one(wtempt,thold,hold);
      }else if(more==1){
        wtempt=wroot;
        update_sender_many(wtempt,thold,templist);
        wtempt=wroot;
        update_receiver_many(wtempt,thold,templist);
      }


      int key=hash_func(thold->trans.sender_ID,senderHashtableNumOfEntries);


      if(sender_hash.hash_array[key]==NULL){

        sender_hash.hash_array[key]=malloc(sizeof(struct bucket_list)); 

        struct bucket_list* buckettemp=sender_hash.hash_array[key];
        add_first(buckettemp,thold,RealBucketSize,0);

      }else{

        struct bucket_list* buckettemp = sender_hash.hash_array[key];
        struct trans_list_hash* breturn=search(buckettemp,thold->trans.sender_ID,RealBucketSize);
        struct trans_list_hash* argument=breturn;
       
        if(breturn==NULL){
          struct bucket_list* buckettemp=sender_hash.hash_array[key];
          add_free(buckettemp,thold,RealBucketSize,0);

        }else{
          add_existing(argument,thold);
        }
        
      }

      int key1=hash_func(thold->trans.receiver_ID,receiverHashtableNumOfEntries);

      if(receiver_hash.hash_array[key1]==NULL){


        receiver_hash.hash_array[key1]=malloc(sizeof(struct bucket_list)); 
        struct bucket_list* buckettemp=receiver_hash.hash_array[key1];
        add_first(buckettemp,thold,RealBucketSize,1);
        


      }else{

        struct bucket_list* buckettemp = receiver_hash.hash_array[key1];
        struct trans_list_hash* breturn=search(buckettemp,thold->trans.receiver_ID,RealBucketSize);
        struct trans_list_hash* argument=breturn;
       
        if(breturn==NULL){
          struct bucket_list* buckettemp=receiver_hash.hash_array[key1];
          add_free(buckettemp,thold,RealBucketSize,1);

        }else{
          add_existing(argument,thold);
        }

      }

      print_transaction(thold->trans);
      printf("Transaction Complete \n");


        struct bit_list* btemp2=templist;
      struct bit_list* bcurr=btemp2;
      struct bit_list* bnext;

      while(bcurr !=NULL){
        //free(bcurr->bp);
        bnext=bcurr->next;
        free(bcurr);

        bcurr=bnext;

      }

      btemp2=NULL;

      templist=NULL;


          sender=NULL;
          receiver=NULL;
          tamount=NULL;
          date1=NULL;
          time1=NULL;

          

          continue;

          }
          free(transline);

          printf("\n");
            Print_Menu();

         
          continue;
      }
    }
   if(strcmp(command,"findEarnings")==0){ //find Earnings is self explanatory
        
          while(command!=NULL){
            
            command = strtok(NULL, " ");

            if(walletearn==NULL){
              walletearn=command;
              continue;
            }
            if(arg1==NULL){
              arg1=command;
              continue; 
            }
            if(arg2==NULL){
              arg2=command;
              continue; 
            }
            if(arg3==NULL){
              arg3=command;
              continue; 
            }
            if(arg4==NULL){
              arg4=command;
              continue; 
            }

            

          }

          if(arg1!=NULL){

          if (arg1[2]==':' && arg2[2]==':'){
            time1=arg1;
            time2=arg2;
            date1=NULL;
            date2=NULL;
          }  
          if (arg1[2]=='-' && arg1[5]=='-' && arg2[2]=='-' && arg2[5]=='-'){
            date1=arg1;
            date2=arg2;
            time1=NULL;
            time2=NULL;
          } 
          if (arg1[2]==':' && arg2[2]=='-' && arg2[5]=='-' && arg3[2]==':' && arg4[2]=='-' && arg4[5]=='-'  ){
            time1=arg1;
            date1=arg2;
            time2=arg3;
            date2=arg4;
          } 

        }



          if((time1!=NULL && time2==NULL) || (time1==NULL && time2!=NULL)){
           printf("Invalid input :/ \n");

            printf("\n");
            Print_Menu();
          walletearn=NULL;
        arg1=NULL;
        arg2=NULL;
        arg3=NULL;
        arg4=NULL;
        time1=NULL;
        time2=NULL;
        date1=NULL;
        date2=NULL;
        continue;
          }
          if((date1!=NULL && date2==NULL) || (date1==NULL && date2!=NULL)){

            printf("Invalid input :/ \n");

            printf("\n");
            Print_Menu();
          walletearn=NULL;
        arg1=NULL;
        arg2=NULL;
        arg3=NULL;
        arg4=NULL;
        time1=NULL;
        time2=NULL;
        date1=NULL;
        date2=NULL;
        continue;
          }

          int nonegiven,allgiven,timesgiven,datesgiven;
          if(time1==NULL && time2==NULL && date1==NULL && date2==NULL){
            nonegiven=1;
            allgiven=0;
            timesgiven=0;
            datesgiven=0;
          }
          if(date1!=NULL && date2!=NULL){
            if(time1==NULL && time2==NULL){
            nonegiven=0;
            allgiven=0;
            timesgiven=0;
            datesgiven=1; 
            }
            sday[0]=date1[0];
            sday[1]=date1[1];
            smonth[0]=date1[3];
            smonth[1]=date1[4];
            syear[0]=date1[6];
            syear[1]=date1[7];
            syear[2]=date1[8];
            syear[3]=date1[9];

            sday2[0]=date2[0];
            sday2[1]=date2[1];
            smonth2[0]=date2[3];
            smonth2[1]=date2[4];
            syear2[0]=date2[6];
            syear2[1]=date2[7];
            syear2[2]=date2[8];
            syear2[3]=date2[9];

            startdate.day=atoi(sday);
            startdate.month=atoi(smonth);
            startdate.year=atoi(syear);
            enddate.day=atoi(sday2);
            enddate.month=atoi(smonth2);
            enddate.year=atoi(syear2);

          }
          if(time1!=NULL && time2!=NULL){
            if(date1==NULL && date2==NULL){
            nonegiven=0;
            allgiven=0;
            timesgiven=1;
            datesgiven=0;
            }
            shour[0]=time1[0];
            shour[1]=time1[1];
            smins[0]=time1[3];
            smins[1]=time1[4];

            shour2[0]=time2[0];
            shour2[1]=time2[1];
            smins2[0]=time2[3];
            smins2[1]=time2[4];
            starttime.hour=atoi(shour);
            starttime.mins=atoi(smins);
            endtime.hour=atoi(shour2);
            endtime.mins=atoi(smins2);
            
          }
          if(time1!=NULL && time2!=NULL && date1!=NULL && date2!=NULL){
            nonegiven=0;
            allgiven=1;
            timesgiven=0;
            datesgiven=0;
          }


          
          if(walletearn[(strlen(walletearn) -1 )]=='\n'){
            walletearn[(strlen(walletearn) -1 )]='\0';
          }

            

          int key=hash_func(walletearn,receiverHashtableNumOfEntries);

          struct bucket_list* buckettemp = receiver_hash.hash_array[key];
          struct trans_list_hash* breturn=search(buckettemp,walletearn,RealBucketSize);
          
       
        if(breturn==NULL){
          
            
          printf("User hasn't participated in any transactions as a receiver :/ \n");

          printf("\n");
            Print_Menu();
          walletearn=NULL;
        arg1=NULL;
        arg2=NULL;
        arg3=NULL;
        arg4=NULL;
        time1=NULL;
        time2=NULL;
        date1=NULL;
        date2=NULL;
        continue;
        }else{
          struct trans_list_hash* forsum=breturn;
          struct trans_list_hash* forprint=breturn;

          int earnings=0;
          while(forsum!=NULL){
            if(datesgiven==1){
            int dresult1=check_dates(forsum->t1->tdate,startdate);
            int dresult2=check_dates(enddate,forsum->t1->tdate);
            if(dresult1==1 && dresult2==1){
              earnings=earnings+forsum->t1->amount;
            }
            }
            if(timesgiven==1){
            int tresult1=check_times(forsum->t1->ttime,starttime);
            int tresult2=check_times(endtime,forsum->t1->ttime);
            if(tresult1==1 && tresult2==1){
              earnings=earnings+forsum->t1->amount;
            }
            }
            if(allgiven==1){
              int dresult1=check_dates(forsum->t1->tdate,startdate);
              int dresult2=check_dates(enddate,forsum->t1->tdate);
             int tresult1=check_times(forsum->t1->ttime,starttime);
             int tresult2=check_times(endtime,forsum->t1->ttime);
             if(dresult1==1 && dresult2==1 && tresult1==1 && tresult2==1){
              earnings=earnings+forsum->t1->amount;
              } 
            }
            if(nonegiven==1){
              earnings=earnings+forsum->t1->amount;
            }


            forsum=forsum->next;
          }
          printf("Earnings are %d\n", earnings);

          
          while(forprint!=NULL){
            if(datesgiven==1){
            int dresult1=check_dates(forprint->t1->tdate,startdate);
            int dresult2=check_dates(enddate,forprint->t1->tdate);
            if(dresult1==1 && dresult2==1){
              struct transaction* temp=forprint->t1;
              print_transaction(*temp);
            }
            }
            if(timesgiven==1){
            int tresult1=check_times(forprint->t1->ttime,starttime);
            int tresult2=check_times(endtime,forprint->t1->ttime);
            if(tresult1==1 && tresult2==1){
              struct transaction* temp=forprint->t1;
              print_transaction(*temp);
            }
            }
            if(allgiven==1){
              int dresult1=check_dates(forprint->t1->tdate,startdate);
              int dresult2=check_dates(enddate,forprint->t1->tdate);
             int tresult1=check_times(forprint->t1->ttime,starttime);
             int tresult2=check_times(endtime,forprint->t1->ttime);
             if(dresult1==1 && dresult2==1 && tresult1==1 && tresult2==1){
              struct transaction* temp=forprint->t1;
              print_transaction(*temp);
              } 
            }
            if(nonegiven==1){
              struct transaction* temp=forprint->t1;
              print_transaction(*temp);
            }


            
            forprint=forprint->next;
          }
          

        }
        printf("\n");
            Print_Menu();
            nonegiven=0;
            allgiven=0;
            timesgiven=0;
            datesgiven=0;

        walletearn=NULL;
        arg1=NULL;
        arg2=NULL;
        arg3=NULL;
        arg4=NULL;
        time1=NULL;
        time2=NULL;
        date1=NULL;
        date2=NULL;

        continue;
        


      } 
      if(strcmp(command,"findPayments")==0){ ////find Payments is self explanatory
      
          while(command!=NULL){
            
     
      
            command = strtok(NULL, " ");

            if(walletpay==NULL){
              walletpay=command;
              continue;
            }
            if(arg1==NULL){
              arg1=command;
              continue; 
            }
            if(arg2==NULL){
              arg2=command;
              continue; 
            }
            if(arg3==NULL){
              arg3=command;
              continue; 
            }
            if(arg4==NULL){
              arg4=command;
              continue; 
            }

      
          }

          if(arg1!=NULL){

           if (arg1[2]==':' && arg2[2]==':'){
            time1=arg1;
            time2=arg2;
            date1=NULL;
            date2=NULL;
          }  
          if (arg1[2]=='-' && arg1[5]=='-' && arg2[2]=='-' && arg2[5]=='-'){
            date1=arg1;
            date2=arg2;
            time1=NULL;
            time2=NULL;
          } 
          if (arg1[2]==':' && arg2[2]=='-' && arg2[5]=='-' && arg3[2]==':' && arg4[2]=='-' && arg4[5]=='-'  ){
            time1=arg1;
            date1=arg2;
            time2=arg3;
            date2=arg4;
          } 

        }

          if((time1!=NULL && time2==NULL) || (time1==NULL && time2!=NULL)){
            printf("Invalid input :/ \n");

            printf("\n");
            Print_Menu();
          walletpay=NULL;
        arg1=NULL;
        arg2=NULL;
        arg3=NULL;
        arg4=NULL;
        time1=NULL;
        time2=NULL;
        date1=NULL;
        date2=NULL;
        continue;
          }
          if((date1!=NULL && date2==NULL) || (date1==NULL && date2!=NULL)){
            printf("Invalid input :/ \n");

            printf("\n");
            Print_Menu();
          walletpay=NULL;
        arg1=NULL;
        arg2=NULL;
        arg3=NULL;
        arg4=NULL;
        time1=NULL;
        time2=NULL;
        date1=NULL;
        date2=NULL;
        continue;
          }

          int nonegiven,allgiven,timesgiven,datesgiven;
          if(time1==NULL && time2==NULL && date1==NULL && date2==NULL){
            nonegiven=1;
            allgiven=0;
            timesgiven=0;
            datesgiven=0;
          }
          if(date1!=NULL && date2!=NULL){
            if(time1==NULL && time2==NULL){
            nonegiven=0;
            allgiven=0;
            timesgiven=0;
            datesgiven=1; 
            }
            sday[0]=date1[0];
            sday[1]=date1[1];
            smonth[0]=date1[3];
            smonth[1]=date1[4];
            syear[0]=date1[6];
            syear[1]=date1[7];
            syear[2]=date1[8];
            syear[3]=date1[9];

            sday2[0]=date2[0];
            sday2[1]=date2[1];
            smonth2[0]=date2[3];
            smonth2[1]=date2[4];
            syear2[0]=date2[6];
            syear2[1]=date2[7];
            syear2[2]=date2[8];
            syear2[3]=date2[9];

            startdate.day=atoi(sday);
            startdate.month=atoi(smonth);
            startdate.year=atoi(syear);
            enddate.day=atoi(sday2);
            enddate.month=atoi(smonth2);
            enddate.year=atoi(syear2);

          }
          if(time1!=NULL && time2!=NULL){
            if(date1==NULL && date2==NULL){
            nonegiven=0;
            allgiven=0;
            timesgiven=1;
            datesgiven=0;
            }
            shour[0]=time1[0];
            shour[1]=time1[1];
            smins[0]=time1[3];
            smins[1]=time1[4];

            shour2[0]=time2[0];
            shour2[1]=time2[1];
            smins2[0]=time2[3];
            smins2[1]=time2[4];
            starttime.hour=atoi(shour);
            starttime.mins=atoi(smins);
            endtime.hour=atoi(shour2);
            endtime.mins=atoi(smins2);
            
          }
          if(time1!=NULL && time2!=NULL && date1!=NULL && date2!=NULL){
            nonegiven=0;
            allgiven=1;
            timesgiven=0;
            datesgiven=0;
          }

       
          if(walletpay[(strlen(walletpay) -1 )]=='\n'){
            walletpay[(strlen(walletpay) -1 )]='\0';
          }
          

          int key=hash_func(walletpay,senderHashtableNumOfEntries);

          struct bucket_list* buckettemp = sender_hash.hash_array[key];
          struct trans_list_hash* breturn=search(buckettemp,walletpay,RealBucketSize);

       
        if(breturn==NULL){
          printf("User hasn't participated in any transactions as a sender :/ \n");

            printf("\n");
            Print_Menu();
          walletearn=NULL;
        arg1=NULL;
        arg2=NULL;
        arg3=NULL;
        arg4=NULL;
        time1=NULL;
        time2=NULL;
        date1=NULL;
        date2=NULL;
        continue;

        }else{
          struct trans_list_hash* forsum=breturn;
          struct trans_list_hash* forprint=breturn;

          int payments=0;
          while(forsum!=NULL){
            if(datesgiven==1){
            int dresult1=check_dates(forsum->t1->tdate,startdate);
            int dresult2=check_dates(enddate,forsum->t1->tdate);
            if(dresult1==1 && dresult2==1){
              payments=payments+forsum->t1->amount;
            }
            }
            if(timesgiven==1){
            int tresult1=check_times(forsum->t1->ttime,starttime);
            int tresult2=check_times(endtime,forsum->t1->ttime);
            if(tresult1==1 && tresult2==1){
              payments=payments+forsum->t1->amount;
            }
            }
            if(allgiven==1){
              int dresult1=check_dates(forsum->t1->tdate,startdate);
              int dresult2=check_dates(enddate,forsum->t1->tdate);
             int tresult1=check_times(forsum->t1->ttime,starttime);
             int tresult2=check_times(endtime,forsum->t1->ttime);
             if(dresult1==1 && dresult2==1 && tresult1==1 && tresult2==1){
              payments=payments+forsum->t1->amount;
              } 
            }
            if(nonegiven==1){
              payments=payments+forsum->t1->amount;
            }
            
            forsum=forsum->next;
          }
          printf("Payments are  %d\n", payments);

          
          while(forprint!=NULL){
            if(datesgiven==1){
            int dresult1=check_dates(forprint->t1->tdate,startdate);
            int dresult2=check_dates(enddate,forprint->t1->tdate);
            if(dresult1==1 && dresult2==1){
              struct transaction* temp=forprint->t1;
              print_transaction(*temp);
            }
            }
            if(timesgiven==1){
            int tresult1=check_times(forprint->t1->ttime,starttime);
            int tresult2=check_times(endtime,forprint->t1->ttime);
            if(tresult1==1 && tresult2==1){
              struct transaction* temp=forprint->t1;
              print_transaction(*temp);
            }
            }
            if(allgiven==1){
              int dresult1=check_dates(forprint->t1->tdate,startdate);
              int dresult2=check_dates(enddate,forprint->t1->tdate);
             int tresult1=check_times(forprint->t1->ttime,starttime);
             int tresult2=check_times(endtime,forprint->t1->ttime);
             if(dresult1==1 && dresult2==1 && tresult1==1 && tresult2==1){
              struct transaction* temp=forprint->t1;
              print_transaction(*temp);
              } 
            }
            if(nonegiven==1){
              struct transaction* temp=forprint->t1;
              print_transaction(*temp);
            }
            
            forprint=forprint->next;
          }
          

        }
        printf("\n");
            Print_Menu();
        nonegiven=0;
            allgiven=0;
            timesgiven=0;
            datesgiven=0;

        walletpay=NULL;
        arg1=NULL;
        arg2=NULL;
        arg3=NULL;
        arg4=NULL;
        time1=NULL;
        time2=NULL;
        date1=NULL;
        date2=NULL;

          continue;
          

      }
      if(strcmp(command,"walletStatus")==0){ //getting how much money the given user has in his wallet
        while(command!=NULL){
            
     
            command = strtok(NULL, " ");

            if(walletsuma==NULL){
              walletsuma=command;
              continue;
            }
           
      
          }


          struct wallet_list* wsuma=wroot;
          int isvalid1=1;
          isvalid1=check_userid(wsuma,walletsuma);
          if(isvalid1==0){
            printf("User does not exist :/ \n");
            printf("\n");
            Print_Menu();
            walletsuma=NULL;
            continue;
          }

          char* tempID=walletsuma;
          
          tempID[(strlen(tempID) -1 )]='\0';

          while(wsuma!=NULL){
            
            if(strcmp(wsuma->wallie.ID,tempID)==0){

              printf("Total money in this wallet: %d\n",wsuma->wallie.total_sum);
              break;
          }
          wsuma=wsuma->next;
          }

          printf("\n");
            Print_Menu();
          walletsuma=NULL;

      continue;


      }
      if(strcmp(command,"bitCoinStatus")==0){ //getting bitcoin's ID, its number of participated transactions and its unspent value
        while(command!=NULL){
          
     
      
            command = strtok(NULL, " ");

            if(bitcoinstat==NULL){
              bitcoinstat=command;
              continue;
            }
           
      
          }

          struct bit_list* bsuma=broot;
          char* tempID=bitcoinstat;
          
          tempID[(strlen(tempID) -1 )]='\0';

          int bfound=0;
          while(bsuma!=NULL){
            
            if(strcmp(bsuma->bp->ID,tempID)==0){
              bfound=1;
              printf("%s ",tempID );
              int counter=0;
              int* g=&counter;
              get_num_of_trans(bsuma->bp,g);
              printf("Number of transactions used %d ",*g);
              printf("Unspent value is %d ",find_right_most(bsuma->bp));
              printf("\n");
              break;
          }
          bsuma=bsuma->next;
          }
          if(bfound==0){
            printf("BitCoin does not exist :/ \n");
             printf("\n");
            Print_Menu();

            bitcoinstat=NULL;
      continue;
          }

          printf("\n");
            Print_Menu();

            bitcoinstat=NULL;
      continue;


      }
      if(strcmp(command,"traceCoin")==0){ //traceCoin prints the transactions in which the bitcoin participated
        while(command!=NULL){
           
     
      
            command = strtok(NULL, " ");

            if(tracecoin==NULL){
              tracecoin=command;
              continue;
            }
           
      
          }

          struct bit_list* bsuma=broot;
          char* tempID=tracecoin;
          
          tempID[(strlen(tempID) -1 )]='\0';

          int tfound=0;
          while(bsuma!=NULL){
            
            if(strcmp(bsuma->bp->ID,tempID)==0){
              tfound=1;
              printf("%s ",tempID );
              
              display(bsuma->bp);
              printf("\n");
              break;
          }
          bsuma=bsuma->next;
          }
          if(tfound==0){
            printf("BitCoin does not exist :/ \n");
            printf("\n");
            Print_Menu();

            tracecoin=NULL;

        continue;
          }

          printf("\n");
            Print_Menu();

            tracecoin=NULL;

      continue;


      }
      if(strcmp(command,"exit\n")==0){ //exiting the menu
          printf("Thank you for using the application! \n");
          break;
      }


      

      break;
     }



    free(line);

    int h1=0;
    int b=0;
    int h2=0;
    

    
   
    //Deleting the allocated memory


    h1=0;
    for(h1;h1<senderHashtableNumOfEntries;h1++){
      struct bucket_list* buckettemp = sender_hash.hash_array[h1];
      while(buckettemp!=NULL){
      
      b=0;
      for(b;b<RealBucketSize;b++){
        if(buckettemp->bucket[b].ID==NULL){
          break;
        }
  
        struct trans_list_hash* rr =buckettemp->bucket[b].root;
        struct trans_list_hash* btemp2=rr;
        struct trans_list_hash* curr=btemp2;
        struct trans_list_hash* bnext;
        while(curr !=NULL){
        bnext=curr->next;
        
        free(curr);
        curr=bnext;
        } 
        btemp2=NULL;

      }
      buckettemp=buckettemp->next;
    }
  }


    h1=0;
    for(h1;h1<senderHashtableNumOfEntries;h1++){
      struct bucket_list* buckettemp = sender_hash.hash_array[h1];
      struct bucket_list* btemp2=buckettemp;
      struct bucket_list* curr=btemp2;
      struct bucket_list* bnext;
      while(curr!=NULL){
        free(curr->bucket);   
        bnext=curr->next;
        free(curr);
        curr=bnext;
    }
  }

   
  free(sender_hash.hash_array);


    h2=0;
    for(h2;h2<receiverHashtableNumOfEntries;h2++){
      struct bucket_list* buckettemp = receiver_hash.hash_array[h2];
      while(buckettemp!=NULL){
      
      b=0;
      for(b;b<RealBucketSize;b++){
        if(buckettemp->bucket[b].ID==NULL){
          break;
        }
  
        struct trans_list_hash* rr =buckettemp->bucket[b].root;
        struct trans_list_hash* btemp2=rr;
        struct trans_list_hash* curr=btemp2;
        struct trans_list_hash* bnext;
        while(curr !=NULL){
        bnext=curr->next;
        free(curr);
        curr=bnext;
        } 
        btemp2=NULL;

      }
      buckettemp=buckettemp->next;
    }
  }


   h2=0;
    for(h2;h2<receiverHashtableNumOfEntries;h2++){
      struct bucket_list* buckettemp = receiver_hash.hash_array[h2];
      struct bucket_list* btemp2=buckettemp;
      struct bucket_list* curr=btemp2;
      struct bucket_list* bnext;
      while(curr!=NULL){
        free(curr->bucket);   
        bnext=curr->next;
        free(curr);
        curr=bnext;
    }
  }

  
  free(receiver_hash.hash_array);


    wtemp=wroot;
    while(wtemp !=NULL){
      
      if(wtemp->wallie.ulr!=NULL){
          
        struct bit_list* current = wtemp->wallie.ulr;
          struct bit_list* next;
          while (current != NULL) {
            next = current->next;
            free(current);
            current = next;
          }
          wtemp->wallie.ulr=NULL;

      }
      wtemp=wtemp->next;
    }

    DestroyWalletList(wroot);

    brtemp=broot;
    while(brtemp !=NULL){
      
      DestroyTree(brtemp->bp);
      
      brtemp=brtemp->next;
    }

    DestroyBitList(broot);
    DestroyTransactionList(troot);

 

}

