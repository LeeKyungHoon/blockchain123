
#include"block.h"

bool running_flag = true;

Block::Block() { header = new Blockheader(); List = new TransactionList(); blockHash = new unsigned char[128]{ 0 };/* tail = nullptr;*/ }

Block::Block(const Block& block) { Block::header = new Blockheader(); Block::List = new TransactionList(); Block::blockHash = nullptr; /*tail = nullptr;*/ Block::header->hs.hashPrevBlock = block.blockHash; }

Blockheader Block::getHeader() { return *Block::header; }

TransactionList Block::getList() { return *Block::List; }

unsigned char * Block::getBlockHash() { return Block::blockHash; }

void Block::makeTransaction(const char * toAddr, const char * value, const char * fee, const char * sMsg) { List->add(new TransactionBase(toAddr, value, fee, sMsg)); }

void Block::makeTransaction(const TransactionBase* tx) { List->add(new TransactionBase(*tx)); }

void Block::mineBlock()
{
	Block::header->setBlockHeader(Block::header->hs.hashPrevBlock, Block::List);
	TransactionUtility::TxUtil util;
	unsigned char* diff = new unsigned char[Block::header->hs.Difficulty]{ 0 };
	int tempNonce = 0;
	for (unsigned int i = 0; i < Block::header->hs.Difficulty + 1; i++) { if (i == Block::header->hs.Difficulty) { diff[i] = '\0'; } else { diff[i] = '0'; } }
	while (running_flag) {
		util.calculateHash(Block::blockHash, Block::header->hs.hashPrevBlock, Block::header->hs.hashMerkleRoot, Block::header->hs.Time, Block::header->hs.Difficulty, Block::header->hs.Nonce);
		if (std::memcmp(Block::blockHash, diff, Block::header->hs.Difficulty) == 0) { break; }
		else { Block::header->hs.Nonce = ++tempNonce; }
	}
	diff = { 0 };
	delete[] diff;

	std::cout << "success mined block" << std::endl;
	std::cout << "mined block hash is " << Block::getBlockHash() << std::endl;
}

Block::~Block() { delete header; delete List; }
