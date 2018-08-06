
#include"merkleTree.h"

using namespace merkle;

void merkleTree::getRoot(unsigned char* & root, const TransactionList& list) {
	//std::vector<unsigned char*> __tempIter;

	if (list.txMap.size() != 0) {
		TransactionUtility::TxUtil util;

		for (std::pair< unsigned char*, TransactionBase> map : list.txMap) {
			__iterator.push_back(map.first);
		}
		while (merkleTree::__iterator.size() != 1) {
			if (merkleTree::__iterator.size() % 2 == 0) {
				for (int i = 0; i < merkleTree::__iterator.size() / 2; i++) {
					util.add(merkleTree::__iterator.at(i), merkleTree::__iterator.at(i + 1));
					util.calculateHash(merkleTree::__iterator.at(i));
					merkleTree::__iterator.erase(merkleTree::__iterator.begin() + (i + 1));
				}
			}
			else {
				for (int i = 0; i < (merkleTree::__iterator.size() / 2) + 1; i++) {
					if ((i * 2) - 1 == merkleTree::__iterator.size() / 2) {
						unsigned char* temp = merkleTree::__iterator.at(i);
						util.add(merkleTree::__iterator.at(i), temp);
						util.calculateHash(merkleTree::__iterator.at(i));
					}
					else {
						util.add(merkleTree::__iterator.at(i), merkleTree::__iterator.at(i + 1));
						util.calculateHash(merkleTree::__iterator.at(i));
						merkleTree::__iterator.erase(merkleTree::__iterator.begin() + (i + 1));
					}
				}
			}
		}


		root = merkleTree::__iterator.at(0);
	}
}

