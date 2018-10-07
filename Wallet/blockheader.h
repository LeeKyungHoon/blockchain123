#pragma once

#include<iostream>
using namespace std;

class Blockheader {

public:
	PUCHAR hashPrevBlock;
	PUCHAR hashMerkleRoot;
	PUCHAR Time;
	UINT Difficulty;
	UINT Nonce;

	Blockheader(){
		hashPrevBlock = new UCHAR[128]{ 0 };
		hashMerkleRoot = new UCHAR[128]{ 0 };
		Time = new UCHAR[128]{ 0 };
		Difficulty = 4;
		Nonce = 0;
	};

	Blockheader(PUCHAR prevHash, PUCHAR merkleRoot, PUCHAR time, UINT diff, UINT nonce)
		:hashPrevBlock(prevHash), hashMerkleRoot(merkleRoot),Time(time),Difficulty(diff), Nonce(nonce) {}
	~Blockheader() {};
};
