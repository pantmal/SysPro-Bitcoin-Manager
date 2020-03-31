#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Tree.h"
#include "Transaction.h"

#define max_size 50

struct trans_list_hash{ //Transaction list for every user

	struct transaction* t1;
	struct trans_list_hash* next;
};

struct bucket_data{ //Bucket data struct contains what is placed at every cell of the bucket array. Specifically, the user's name and the head of a linked list of pointers to struct transaction
	
	char* ID;
	struct trans_list_hash* root;	

};

struct bucket_list{ //Bucket list node contains an array of struct bucket data(in other words,the bucket), a pointer to the next node, and information of whether the bucket is full or not
	int counter;
	bool isfull;
	struct bucket_data* bucket;
	struct bucket_list* next;
};

struct hash_table{ //Hash table has an array in which every cell contains the head of a list of buckets
	struct bucket_list** hash_array;
};


//Functions will be explained in the .c file

int hash_func(char* user, int entries); 

void add_first(struct bucket_list* buckettemp, struct trans_list* tt, int bucketsize, int sr);

struct trans_list_hash* search(struct bucket_list* buckettemp,char* user, int bucketsize);

void add_existing(struct trans_list_hash* bucket_root, struct trans_list* tt);

void add_free(struct bucket_list* buckettemp, struct trans_list* tt, int bucketsize, int sr);

#endif