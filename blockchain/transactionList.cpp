
#include"transactionList.h"

TransactionList::TransactionList() { TransactionList::txMap.clear(); }

TransactionList::TransactionList(const transactionMap& txBase) { if (txMap.empty()) { txMap = txBase; } else { for (std::pair<unsigned char*, TransactionBase> tm : txBase) { txMap.insert(tm); } } }

TransactionList::TransactionList(const TransactionList & list)
{
	txMap = list.txMap;
}

void TransactionList::add(const TransactionBase *tx) { txMap.insert(std::pair<unsigned char*, TransactionBase>(tx->txHash, *tx)); }

void TransactionList::add(unsigned char * hash, TransactionBase t)
{
	txMap.insert(std::pair<unsigned char*, TransactionBase>(hash, t));
}

void TransactionList::getLastElem(TransactionBase & tx)
{
	for (auto it = this->txMap.begin(); it != this->txMap.end(); ++it) {
		if (!it->second.txSign) {
			tx = it->second;
			break;
		}
	}
}

TransactionBase* TransactionList::getLastElem()
{
	TransactionBase* tx = nullptr;
	for (auto it = this->txMap.begin(); it != this->txMap.end(); ++it) {
		if (!it->second.txSign) {
			tx = &it->second;
			break;
		}
	}
	return tx;
}
