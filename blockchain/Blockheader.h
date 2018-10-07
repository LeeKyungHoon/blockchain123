
#include"merkleTree.h"

class Blockheader : public merkle::merkleTree, public TransactionUtility::TxUtil {

public:
	unsigned char* hashPrevBlock;
	unsigned char* hashMerkleRoot;
	unsigned char* Time;
	unsigned int Difficulty;
	unsigned int Nonce;

public: //function
	Blockheader() { setNull(); };
	Blockheader(const Blockheader &header) :hashPrevBlock(header.hashPrevBlock),
		hashMerkleRoot(header.hashMerkleRoot),
		Time(header.Time),
		Difficulty(header.Difficulty),
		Nonce(header.Nonce) {};

	Blockheader(unsigned char* hashPrevBlock, const TransactionList & list) :hashPrevBlock(hashPrevBlock) {
		getRoot(hashMerkleRoot, list);
		getTime(Time);
	};

	Blockheader(unsigned char * hashPrevBlock,
		unsigned char* hashMerkleRoot,
		unsigned char * time,
		unsigned int difficulty,
		unsigned int Nonce) :
		hashPrevBlock(hashPrevBlock),
		hashMerkleRoot(hashMerkleRoot),
		Time(time),
		Difficulty(difficulty),
		Nonce(Nonce) {};

	void setNull() {
		hashPrevBlock = new unsigned char[128]{ 0 };
		hashMerkleRoot = new unsigned char[128]{ 0 };
		Time = new unsigned char[128]{ 0 };
		Difficulty = 4;
		Nonce = 0;
	};

	void setBlockHeader(unsigned char* hashPrevBlock, const TransactionList &list) {
		this->hashPrevBlock = hashPrevBlock;
		getRoot(hashMerkleRoot, list);
		getTime(Time);
	};
};


