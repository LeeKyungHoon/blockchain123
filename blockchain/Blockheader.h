
class Blockheader {
	

public :

	//int32_t version;//버전을 사용하지 않음;
	unsigned char *hashPrevBlock;
	unsigned char *hashMerkleTree;
	unsigned int Time;
	unsigned int Difficulty;
	unsigned int Nonce;

	Blockheader();
	void setNull() ;
	void setBlockheader(unsigned char *hashPrevBlock, unsigned char *hashMerkleTree, unsigned int Time, unsigned int Difficulty, unsigned int Nonce);

};

Blockheader::Blockheader() {
	setNull();
};

inline void Blockheader::setNull() {
	hashPrevBlock = 0;
	hashMerkleTree = 0;
	Time = 0;
	Difficulty = 0;
	Nonce = 0;
};


