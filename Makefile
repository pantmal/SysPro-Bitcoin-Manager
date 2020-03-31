CC=gcc

CFLAGS=-c
all: bitcoin

bitcoin: Hash_Table.o Tree.o Transaction.o Wallet.o bitcoin.o 
	$(CC) -o bitcoin Hash_Table.o Tree.o Transaction.o Wallet.o bitcoin.o

Hash_Table.o: Hash_Table.c
	$(CC) $(CFLAGS) Hash_Table.c

Tree.o: Tree.c 
	$(CC) $(CFLAGS) Tree.c

Transaction.o: Transaction.c 
	$(CC) $(CFLAGS) Transaction.c

Wallet.o: Wallet.c 
	$(CC) $(CFLAGS) Wallet.c

bitcoin.o: bitcoin.c
	$(CC) $(CFLAGS) bitcoin.c
clean:
	rm -rf *o bitcoin
