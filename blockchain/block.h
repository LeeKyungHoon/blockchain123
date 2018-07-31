
#include"Blockheader.h"
#include"transactionList.h"
class Block {
private:
	Blockheader header;
	TransactionList List;

public:
	Block();
	void setNull();
	Blockheader getHeader();
};

inline Block::Block() {
	setNull();
}

inline void Block::setNull()
{
	Block::header.setNull();
}

Blockheader Block::getHeader() {
	Blockheader block;
	block.hashPrevBlock = header.hashPrevBlock;
	block.hashMerkleTree = header.hashMerkleTree;
	block.Time = header.Time;
	block.Difficulty = header.Difficulty;
	block.Nonce = header.Nonce;
}






