
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

void Blockchain::occurTransaction(std::string toAddr, std::string value, std::string nonce, std::string contents)
{
	chain.back()->makeTransaction(toAddr.c_str(), value.c_str(), nonce.c_str(), contents.c_str());
}
