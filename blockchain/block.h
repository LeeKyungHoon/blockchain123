
#include"Blockheader.h"
#include"transactionList.h"
class Block {

public: // arg
	Blockheader header;
	TransactionList List;


public: //function
	Block();
	Block(const Block&);
	void setNull();
	Blockheader getHeader();
	TransactionList getList();
	void makeTransaction(const unsigned char* toAddr, const unsigned char* value, const unsigned char* nonce, const unsigned char* contents);
};







