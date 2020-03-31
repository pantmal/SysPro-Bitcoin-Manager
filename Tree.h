#ifndef TREE_H
#define TREE_H

#pragma once

/*To implement the Tree structure I used the source: "Η γλωσσα C σε βαθος" */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define max_size 50 //max_size is set to 50 for the IDs

#include "Transaction.h" 


struct tree_node {  //Tree Node struct holds all the necessary information for every bitcoin

	int data;		  //This member holds the real value of one bitcoin. For example if user A sends user B some money, and B decides to send back some money with the same bitcoin, this amount will be returned here
	int originaldata; //Original data is the amount that has not been used in any transaction. It is used to help calculate the "unspent" in the bitCoinStatus command
	char ID[max_size]; //Bitcoin's ID
	char user[max_size]; //The user who has this bitcoin
	
	bool isleft; //Isleft and isright are used so we can know in which node we are
	bool isright;
	bool allspent; //If originaldata reaches 0 then allspent is set to 1 so we can know that all of its original value was spent
	
	struct tree_node* left; //Left and right nodes
	struct tree_node* right;

	struct transaction* transp; //All left nodes have a pointer to a struct transaction that will be used in the traceCoin command
};

struct bit_list{ //Bit list is list of tree nodes

	struct tree_node* bp;
	struct bit_list* next;	
	
};

//The functions will be explained in the .c file

struct tree_node* newnode(int n, char* ID, char* user);

int find_right_most(struct tree_node* rt);

void display(struct tree_node* ptr);

void get_num_of_trans(struct tree_node* ptr,int* g);

struct bit_list* get_last_bit(struct bit_list* bt);

void break_bitcoin(struct tree_node* hold, struct trans_list* thold );

void break_bitcoin_list(struct bit_list* templist, struct trans_list* thold );

void DestroyTree(struct tree_node* root);

void DestroyBitList(struct bit_list* broot);

#endif