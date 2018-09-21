
#include"block.h"

bool running_flag = true;

Block::Block() { 
	header = new Blockheader(); 
	List = new TransactionList(); 
	blockHash = new unsigned char[128]{ 0 }; 
}

Block::Block(const Block& block) { 
	//header = block.header;
	//List = block.List;

	header = new Blockheader(*block.header);
	List = new TransactionList(*block.List);
	blockHash = new unsigned char[128]{ 0 };
	memcpy_s(blockHash, _msize(blockHash), block.blockHash, _msize(block.blockHash));
}

Block::Block(unsigned char * hash, const Blockheader & h, const TransactionList & l)
{
	blockHash = new unsigned char[128]{ 0 };
	memcpy_s(blockHash, _msize(blockHash), hash, _msize(hash));
	header = new Blockheader(h);
	List = new TransactionList(l);
}

Blockheader Block::getHeader() { return *header; }

TransactionList Block::getList() { return *List; }

unsigned char * Block::getBlockHash() { return blockHash; }

void Block::makeTransaction(const char * toAddr, const char * value, const char * fee, const char * sMsg) { List->add(new TransactionBase(toAddr, value, fee, sMsg)); }

void Block::makeTransaction(const TransactionBase* tx) { List->add(new TransactionBase(*tx)); }

void Block::mineBlock(const Block & prevBlock)
{
	header->setBlockHeader(prevBlock.blockHash, *List);
	unsigned char* diff = new unsigned char[header->Difficulty]{ 0 };
	int tempNonce = 0;
	for (unsigned int i = 0; i < header->Difficulty + 1; i++) { if (i == header->Difficulty) { diff[i] = '\0'; } else { diff[i] = '0'; } }
	while (running_flag) {
		calculateHash(blockHash, header->hashPrevBlock, header->hashMerkleRoot, header->Time, header->Difficulty, header->Nonce);
		if (std::memcmp(blockHash, diff, header->Difficulty) == 0) { break; }
		else { header->Nonce = ++tempNonce; }
	}
	diff = { 0 };
	delete[] diff;

	std::cout << "success mined block" << std::endl;
	std::cout << "mined block hash is " << getBlockHash() << std::endl;
}

void Block::stopMining()
{
	running_flag = false;
}

void Block::startMining()
{
	running_flag = true;
}

Block::~Block() { delete header; delete List; /*delete[] blockHash;*/ }
