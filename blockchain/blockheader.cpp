
#include"Blockheader.h"

Blockheader::Blockheader() {
	setNull();
};

Blockheader::Blockheader(const Blockheader& header) {
	setNull();
	Blockheader::Blockheader(header.hs.hashPrevBlock, header.hs.hashMerkleRoot, header.hs.Difficulty, header.hs.Nonce);
}

Blockheader::Blockheader(unsigned char * hashPrevBlock, unsigned char *hashMerkleRoot, unsigned char * difiiculty, unsigned char * Nonce)
{
	setNull();
	hs.hashPrevBlock = hashPrevBlock;
	hs.hashMerkleRoot = hashMerkleRoot;
	hs.Difficulty = difiiculty;
	hs.Nonce = Nonce;
}

void Blockheader::setNull() {
	hs.hashPrevBlock = 0;
	hs.hashMerkleRoot = 0;
	hs.Time = 0;
	hs.Difficulty = 0;
	hs.Nonce = 0;
}

