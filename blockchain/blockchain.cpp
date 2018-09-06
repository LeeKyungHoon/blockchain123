#pragma once

#include"blockchain.h"

Blockchain::Blockchain()
{
	Blockchain::geneBlock();
}


void Blockchain::geneBlock()
{
	chain.push_back(new Block());
	chain.back()->mineBlock();
}

void Blockchain::makeNewBlock()
{
	chain.push_back(new Block());
}

void Blockchain::mineBlock() {
	chain.back()->mineBlock();
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

void Blockchain::rcv_block(Block block)
{
	chain.push_back(new Block(block));

}


