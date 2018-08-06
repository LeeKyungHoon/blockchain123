
#include"blockchain.h"

Blockchain::Blockchain()
{
	Blockchain::geneBlock();
}


void Blockchain::geneBlock()
{
	Blockchain::firstBlock = new Block();
	Blockchain::firstBlock->mineBlock();
}

void Blockchain::makeNewBlock()
{
	Blockchain::curBlockNode = new Block(*this->firstBlock);
}

void Blockchain::mineBlock() {
	curBlockNode->mineBlock();
	curBlockNode->tail = firstBlock;
	firstBlock = curBlockNode;
}

void Blockchain::occurTransaction()
{
	Blockchain::curBlockNode->makeTransaction("100", "100", "100", "100");
}

void Blockchain::printBC()
{
	Block * temp = firstBlock;

	while (temp->tail != nullptr) {
		printf("%s\n", temp->blockHash);
		temp = temp->tail;
	}

}


void makeBlock(Blockchain * bc)
{
	for (int i = 0; i < 3; i++) {
	bc->makeNewBlock();
	bc->mineBlock();
	}
	bc->printBC();

}

void tx(Blockchain * chain)
{
	chain->occurTransaction();
}


int main(void) {
	Blockchain * newchain = new Blockchain();
	
	time_t cTime = time(0);
	newchain->makeNewBlock();
	newchain->occurTransaction();
	newchain->mineBlock();
	time_t fTime = time(0);
	newchain->printBC();
	printf("\n%lld\n", fTime - cTime);
	newchain->makeNewBlock();
	newchain->occurTransaction();
	newchain->mineBlock();
	time_t sTime = time(0);
	newchain->printBC();
	printf("\n%lld\n", sTime - fTime);
	newchain->makeNewBlock();
	newchain->occurTransaction(); 
	newchain->mineBlock();
	time_t tTime = time(0);
	newchain->printBC();
	printf("\n%lld\n", tTime - sTime);
	//std::thread first(&makeBlock, newchain);
	////std::thread second(&Blockchain::occurTransaction);

	//first.join();
	////second.join();





	system("pause");
	return 0;
}