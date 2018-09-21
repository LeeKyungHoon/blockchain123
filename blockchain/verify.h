#include"blockchain.h"

int verify(const Block &b) {
	Blockchain * chain = Blockchain::GetInstance();

	size_t s = 0;

	for (std::vector<Block*>::iterator it = chain->getChain().end(); it != chain->getChain().begin();--it) {
		Block cb = **it;

		if (cb.hashPrevBlock == b.hashPrevBlock) {
			return s;
		}

		s++;

	}


	return -1;
}
