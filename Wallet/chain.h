#pragma once

#include"block.h"

class blockchain {
private:
	vector<Block> chain;
	blockchain() {};
	~blockchain() {};
public:
	static blockchain* GetInstance() { static blockchain chain; return &chain; }
	void add(Block b) { chain.push_back(b); }
};