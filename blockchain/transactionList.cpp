
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

TransactionBase TransactionList::getLastElem()
{
	std::unordered_map<unsigned char*, TransactionBase>::iterator it = txMap.end();
	return it->second;
}
