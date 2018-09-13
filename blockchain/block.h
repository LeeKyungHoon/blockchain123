#pragma once


#include"Blockheader.h"

extern bool running_flag;

class Block :public Blockheader{

public: // arg
	Blockheader *header;
	TransactionList *List;
	unsigned char* blockHash;
	//Block * tail;

	


public: //function
	Block();
	Block(const Block& block);
	Block(unsigned char* hash, const Blockheader & h, const TransactionList & l);
	Blockheader getHeader();
	TransactionList getList();
	unsigned char* getBlockHash();
	void makeTransaction(const char * toAddr, const char * value, const char * fee, const char * sMsg);
	void makeTransaction(const TransactionBase*);
	void mineBlock(const Block & prevBlock);
	~Block();
};







