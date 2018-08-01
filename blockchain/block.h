
#include"Blockheader.h"
#include"transactionList.h"

class Block {

public: // arg
	Blockheader *header;
	TransactionList *List;


public: //function
	Block();
	Block(const Block&);
	Blockheader getHeader();
	TransactionList getList();
	void makeTransaction(const char* toAddr, const char* value, const char* nonce, const char* contents);
	~Block();
};







