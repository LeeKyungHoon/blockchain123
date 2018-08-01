
#include"block.h"


Block::Block() { header = new Blockheader(); List = new TransactionList(); }

Block::Block(const Block& block) { header = block.header; List = block.List; }

Blockheader Block::getHeader() { return *header; }

TransactionList Block::getList() { return *List; }

void Block::makeTransaction(const char * toAddr, const char * value, const char * nonce, const char * contents)
{
	List->add(new TransactionBase(toAddr, value, nonce, contents));

}

Block::~Block() {
	delete header;
	delete List;
}


int main(void) {

	Block *block1 = new Block();
	Block *block2 = new Block();
	block1->makeTransaction("100", "100", "100", "100");
	block2->makeTransaction("200", "200", "200", "200");

	for (std::pair<unsigned char*, TransactionBase> map : block1->List->txMap) {
		printf("map stored hash : %s\n txHash : %s\n txAddr : %s\n txVal : %s\n txNonce : %s\n txCont : %s\n txTime : %s\n", map.first, map.second.txHash, map.second.txToAddr, map.second.txVal, map.second.txNonce, map.second.txCont, map.second.txTime);
	}

	for (std::pair<unsigned char*, TransactionBase> map : block2->List->txMap) {
		printf("map stored hash : %s\n txHash : %s\n txAddr : %s\n txVal : %s\n txNonce : %s\n txCont : %s\n txTime : %s\n", map.first, map.second.txHash, map.second.txToAddr, map.second.txVal, map.second.txNonce, map.second.txCont, map.second.txTime);
	}

	system("pause");

	return 0;
}