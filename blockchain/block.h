
#include<time.h>
#include"Blockheader.h"
#include"Transaction.h"

class Block :public Blockheader {
private:
	Blockheader header;
	Transaction blockTx;
public:
	Block(Blockheader header, Transaction Tx);
	void setNull();
	Blockheader getHeader();
	Transaction getTransaction();
};

inline Block::Block(Blockheader header, Transaction Tx) {
	setNull();
}

inline void Block::setNull()
{
	Block::header = Blockheader::setNull();
	Block::blockTx = Transaction::setNull();
}






