
#include"block.h"


Block::Block() { header = new Blockheader(); List = new TransactionList(); blockHash = 0; }

Block::Block(const Block& block) { Block::header = block.header; Block::List = block.List; Block::blockHash = block.blockHash; }

Blockheader Block::getHeader() { return *Block::header; }

TransactionList Block::getList() { return *Block::List; }

unsigned char * Block::getBlockHash() { return Block::blockHash; }

void Block::makeTransaction(const char * toAddr, const char * value, const char * nonce, const char * contents)
{
	List->add(new TransactionBase(toAddr, value, nonce, contents));
}
void Block::mineBlock()
{
	Block::header = new Blockheader((unsigned char*)"0", Block::List);
	TransactionUtility::TxUtil util;
	unsigned char* diff = new unsigned char[Block::header->hs.Difficulty];
	int tempNonce = 0;

	for (unsigned int i = 0; i < Block::header->hs.Difficulty; i++) {
		diff[i] = '0';
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

}
//block chain에서 작성
//void Block::makeGeneBlock() {
//	new Block();
//}


Block::~Block() {
	delete header;
	delete List;
}


int main(void) {
	unsigned char* mRoot = new unsigned char[64]{ 0 };
	merkle::merkleTree merkleT;

	Block *block1 = new Block();
	Block *block2 = new Block();
	block1->makeTransaction("100", "100", "100", "100");
	block1->makeTransaction("100", "100", "100", "100");
	block1->makeTransaction("100", "100", "100", "100");
	block1->makeTransaction("100", "100", "100", "100");
	block1->makeTransaction("100", "100", "100", "100");
	block1->makeTransaction("100", "100", "100", "100");
	block1->makeTransaction("100", "100", "100", "100");
	block1->makeTransaction("100", "100", "100", "100");
	block1->makeTransaction("100", "100", "100", "100");
	block1->makeTransaction("100", "100", "100", "100");
	block1->makeTransaction("100", "100", "100", "100");
	block1->makeTransaction("100", "100", "100", "100");
	block1->makeTransaction("100", "100", "100", "100");
	block1->makeTransaction("100", "100", "100", "100");
	block2->makeTransaction("200", "200", "200", "200");

	//for (std::pair<unsigned char*, TransactionBase> map : block1->List->txMap) {
	//	printf("map stored hash : %s\n txHash : %s\n txAddr : %s\n txVal : %s\n txNonce : %s\n txCont : %s\n txTime : %s\n", map.first, map.second.txHash, map.second.txToAddr, map.second.txVal, map.second.txNonce, map.second.txCont, map.second.txTime);
	//}

	//for (std::pair<unsigned char*, TransactionBase> map : block2->List->txMap) {
	//	printf("map stored hash : %s\n txHash : %s\n txAddr : %s\n txVal : %s\n txNonce : %s\n txCont : %s\n txTime : %s\n", map.first, map.second.txHash, map.second.txToAddr, map.second.txVal, map.second.txNonce, map.second.txCont, map.second.txTime);
	//}

	//Blockheader * header = new Blockheader(block1->blockHash, block1->List);
	//block1->header = header;

	//printf("block1 difficulty : %s\n block1 merkleRoot : %s\n block1 hashPrevBlock : %s\n block1 nonce : %s\n block1 time : %s\n", block1->header->hs.Difficulty, block1->header->hs.hashMerkleRoot, block1->header->hs.hashPrevBlock, block1->header->hs.Nonce, block1->header->hs.Time);

	//merkleT.getRoot(mRoot, block1->List->txMap);

	//printf("block1 list merkle root : %s\n", mRoot);

	block1->mineBlock();

	printf("block hash : %s", block1->blockHash);

	system("pause");

	return 0;
}