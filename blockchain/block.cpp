
#include"block.h"


Block::Block() { header = new Blockheader(); List = new TransactionList(); blockHash = nullptr; tail = nullptr; }

Block::Block(const Block& block) { Block::header = new Blockheader(); Block::List = new TransactionList(); Block::blockHash = nullptr; tail = nullptr; Block::header->hs.hashPrevBlock = block.blockHash; }

Blockheader Block::getHeader() { return *Block::header; }

TransactionList Block::getList() { return *Block::List; }

unsigned char * Block::getBlockHash() { return Block::blockHash; }

void Block::makeTransaction(const char * toAddr, const char * value, const char * nonce, const char * contents)
{
	List->add(new TransactionBase(toAddr, value, nonce, contents));
}
void Block::mineBlock()
{
	Block::header->setBlockHeader(Block::header->hs.hashPrevBlock, Block::List);
	TransactionUtility::TxUtil util;
	unsigned char* diff = new unsigned char[Block::header->hs.Difficulty];
	int tempNonce = 0;

	for (unsigned int i = 0; i < Block::header->hs.Difficulty + 1; i++) {
		if (i == Block::header->hs.Difficulty) {
			diff[i] = '\0';
		}
		else {
			diff[i] = '0';
		}
	}

	while (true) {
		util.calculateHash(Block::blockHash, Block::header->hs.hashPrevBlock, Block::header->hs.hashMerkleRoot, Block::header->hs.Time, Block::header->hs.Difficulty, Block::header->hs.Nonce);

		//if (std::string((const char*)blockHash).substr(0, (int)(Block::header->hs.Difficulty)).compare(std::string((const char*)diff)) == 0) {
		//	break;
		//}
		if (std::memcmp(Block::blockHash, diff, Block::header->hs.Difficulty) == 0) {
			break;
		}
		else {
			Block::header->hs.Nonce = ++tempNonce;
		}
	}

	delete[] diff;

}
//block chain에서 작성
//void Block::makeGeneBlock() {
//	new Block();
//}


Block::~Block() {
	delete header;
	delete List;
}


//int main(void) {
//	Block *block1 = new Block();
//	Block *block2 = new Block();
//	block1->makeTransaction("100", "100", "100", "100");
//	block1->makeTransaction("100", "100", "100", "100");
//	block1->makeTransaction("100", "100", "100", "100");
//	block1->makeTransaction("100", "100", "100", "100");
//	block1->makeTransaction("100", "100", "100", "100");
//	block1->makeTransaction("100", "100", "100", "100");
//	block1->makeTransaction("100", "100", "100", "100");
//	block1->makeTransaction("100", "100", "100", "100");
//	block1->makeTransaction("100", "100", "100", "100");
//	block1->makeTransaction("100", "100", "100", "100");
//	block1->makeTransaction("100", "100", "100", "100");
//	block1->makeTransaction("100", "100", "100", "100");
//	block1->makeTransaction("100", "100", "100", "100");
//	block1->makeTransaction("100", "100", "100", "100");
//	block2->makeTransaction("200", "200", "200", "200");
//
//	block1->mineBlock();
//
//	printf("block hash : %s", block1->blockHash);
//
//	system("pause");
//
//	return 0;
//}