#ifndef WALLET_H
#define WALLET_H

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Tree.h"
#include "Transaction.h"

#define max_size 50


struct wallet{ //Struct wallet represents the users participating in the application

	char ID[max_size]; //His name
	struct bit_list* ulr; //A list of bitcoins he has
	int total_sum; //The full amount of all his bitcoins
	
};

struct wallet_list{ //List with the users
	
	struct wallet wallie;
	struct wallet_list* next;
};

//The functions will be explained in the .c file

struct wallet_list* new_wallet(struct wallet temp);

struct wallet_list* get_last_wallet(struct wallet_list* wt);

void calculate_sum(struct wallet_list* wt);

int how_many(struct wallet_list* wt, struct trans_list* tt);

struct tree_node* get_bitcoin(struct wallet_list* wt, struct trans_list* tt);

struct bit_list* get_bitcoin_list(struct wallet_list* wt, struct trans_list* tt);

void update_sender_one(struct wallet_list* wt, struct trans_list* tt, struct tree_node* hold );

void update_sender_many(struct wallet_list* wt, struct trans_list* tt, struct bit_list* templist);

void update_receiver_one(struct wallet_list* wt, struct trans_list* tt, struct tree_node* hold);

void update_receiver_many(struct wallet_list* wt, struct trans_list* tt, struct bit_list* templist);

void DestroyWalletList(struct wallet_list* wroot);

int check_userid(struct wallet_list* wroot, char* ID);

int check_amount(struct wallet_list* wroot, char* ID,int amount);

int is_same(char* ID1,char* ID2);


#endif