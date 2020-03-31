#ifndef TRANSACTION_H
#define TRANSACTION_H

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



#define max_size 50

struct date{ //Date and time structs are defined here
	int day;
	int month;
	int year;
};

struct time{
	int hour;
	int mins;
	
};

struct transaction{ //Struct transaction has the ID, sender/receiver's ID, the amount sent/received, and date/times

	char ID[max_size];
	char sender_ID[max_size];
	char receiver_ID[max_size];
	int amount;
	struct date tdate;
	struct time ttime;
};


struct trans_list{ //List of transactions

	struct transaction trans;
	struct trans_list* next;
};

//Functions will be explained in the .c file

struct trans_list* get_last_trans(struct trans_list* trt);

int check_times(struct time t1, struct time t2);

int check_dates(struct date d1, struct date d2 );

void DestroyTransactionList(struct trans_list* troot);

int check_id(char* ID,struct trans_list* troot);

void print_transaction(struct transaction tp);

#endif