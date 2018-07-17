
#include"Blockheader.h"
#include"Transaction.h"

class Block :public Blockheader {
private:
	Blockheader header;
	Transaction blockTx;
public:
	Block();
	void setNull();
	Blockheader getHeader();
	Transaction getTransaction();
};

inline Block::Block() {
	setNull();
}

inline void Block::setNull()
{
	Block::header.setNull();
	Block::blockTx.setNull();
}

Blockheader Block::getHeader() {
	Blockheader block;
	block.hashPrevBlock = hashPrevBlock;
	block.hashMerkleTree = hashMerkleTree;
	block.Time = Time;
	block.Difficulty = Difficulty;
	block.Nonce = Nonce;
}






