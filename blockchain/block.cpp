
#include"block.h"


inline Block::Block() {
	setNull();
}

inline Block::Block(const Block& block) {
	setNull();
	header = block.header;
	List = block.List;
}

inline void Block::setNull()
{
	Block::header.setNull();
}

Blockheader Block::getHeader() {

	return this->header;

}

TransactionList Block::getList() {
	return this->List;
}

void Block::makeTransaction(const unsigned char * toAddr, const unsigned char * value, const unsigned char * nonce, const unsigned char * contents)
{

}


int main(void) {

	Block block;

}