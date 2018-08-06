
#include"merkleTree.h"

typedef struct headerStruct
{
	unsigned char* hashPrevBlock;
	unsigned char* hashMerkleRoot;
	unsigned char* Time;
	unsigned int Difficulty;
	unsigned int Nonce;
}header;

class Blockheader {

public:
	header hs;
	merkle::merkleTree merkleT;
	TransactionUtility::TxUtil util;

public: //function
	Blockheader();
	Blockheader(const Blockheader&);
	Blockheader(unsigned char* ,const TransactionList *);
	Blockheader(unsigned char *, unsigned char*, unsigned int, unsigned int);
	void setNull();
	void setBlockHeader(unsigned char*, const TransactionList *);

};


