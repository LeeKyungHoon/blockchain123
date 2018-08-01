
#include"merkleTree.h"

typedef struct headerStruct
{
	unsigned char* hashPrevBlock;
	unsigned char* hashMerkleRoot;
	unsigned char* Time;
	unsigned char* Difficulty;
	unsigned char* Nonce;
}header;

class Blockheader {

public:
	header hs;

public: //function
	Blockheader();
	Blockheader(const Blockheader&);
	Blockheader(unsigned char *, unsigned char*, unsigned char*, unsigned char*);
	void setNull();

};


