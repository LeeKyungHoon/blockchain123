#pragma once


#include"Blockheader.h"

extern bool running_flag;

class Block {

public: // arg
	Blockheader *header;
	TransactionList *List;
	unsigned char* blockHash;
	//Block * tail;

	


public: //function
	Block();
	Block(const Block&);
	Blockheader getHeader();
	TransactionList getList();
	unsigned char* getBlockHash();
	void makeTransaction(const char* toAddr, const char* value, const char* fee, const char* sMsg);
	void makeTransaction(const TransactionBase*);
	void mineBlock();
	~Block();
};







