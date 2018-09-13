
#include"block.h"

#pragma once

class Blockchain {
private:
	std::vector<Block*> chain;
	Blockchain();
	~Blockchain() {};
public:
	static Blockchain* GetInstance() { static Blockchain blockchain; return &blockchain; }
	void geneBlock();
	void makeNewBlock();
	void mineBlock();
	void occurTransaction(std::string, std::string, std::string, std::string);
	void occurTransaction(const TransactionBase * tx);
	std::vector<Block*> getChain();
	void rcv_block(const Block &block);
	void rmvAll() { chain.clear(); };
};