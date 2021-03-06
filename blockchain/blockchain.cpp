#pragma once

#include"blockchain.h"

Blockchain::Blockchain()
{
	Blockchain::geneBlock();
}


void Blockchain::geneBlock()
{
	chain.push_back(new Block());
	chain.back()->mineBlock(chain.back());
}

void Blockchain::makeNewBlock()
{
	chain.push_back(new Block());
}

void Blockchain::mineBlock() {
	std::vector<Block*>::iterator it = chain.begin();
	const size_t chain_size = chain.size();
	//chain.back()->mineBlock(chain.end()[-2]);
	chain.back()->mineBlock(*(it+(chain_size-1)));
}

void Blockchain::occurTransaction(std::string toAddr, std::string value, std::string fee, std::string sMsg)
{
	chain.back()->makeTransaction(toAddr.c_str(), value.c_str(), fee.c_str(), sMsg.c_str());
}

void Blockchain::occurTransaction(const TransactionBase * tx) 
{
	chain.back()->makeTransaction(tx);
}

std::vector<Block*> Blockchain::getChain()
{
	return this->chain;
}

void Blockchain::rcv_block(const Block &block)
{
	chain.push_back(new Block(block));

}


