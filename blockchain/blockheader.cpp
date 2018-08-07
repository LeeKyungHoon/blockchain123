
#include"Blockheader.h"

Blockheader::Blockheader() { setNull(); };

Blockheader::Blockheader(const Blockheader& header) { setNull(); Blockheader::Blockheader(header.hs.hashPrevBlock, header.hs.hashMerkleRoot, header.hs.Difficulty, header.hs.Nonce); }

Blockheader::Blockheader(unsigned char* hashPrevBlock, const TransactionList* list) { setNull(); hs.hashPrevBlock = hashPrevBlock; merkleT.getRoot(hs.hashMerkleRoot, *list); util.getTime(hs.Time); }

Blockheader::Blockheader(unsigned char * hashPrevBlock, unsigned char *hashMerkleRoot, unsigned int difiiculty, unsigned int Nonce) { setNull(); hs.hashPrevBlock = hashPrevBlock; hs.hashMerkleRoot = hashMerkleRoot; hs.Difficulty = difiiculty; hs.Nonce = Nonce; }

void Blockheader::setNull() { hs.hashPrevBlock = nullptr; hs.hashMerkleRoot = nullptr; hs.Time = nullptr; hs.Difficulty = 4; hs.Nonce = 0; }

void Blockheader::setBlockHeader(unsigned char* hashPrevBlock, const TransactionList* list) { setNull(); hs.hashPrevBlock = hashPrevBlock; merkleT.getRoot(hs.hashMerkleRoot, *list); util.getTime(hs.Time); }

