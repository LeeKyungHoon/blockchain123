#pragma once

#include"blockheader.h"
#include"transactionList.h"

class Block {

public:
	Blockheader * header;
	TransactionList *List = TransactionList::GetInstance();
	PUCHAR blockHash;

	Block() {};
	Block(PUCHAR hash, Blockheader h) {
		blockHash = new unsigned char[128]{ 0 };
		memcpy_s(blockHash, _msize(blockHash), hash, _msize(hash));
		header = new Blockheader(h);
	};
	~Block() {};
};