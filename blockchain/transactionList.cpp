
#include"transactionList.h"

TransactionList::TransactionList() { TransactionList::txMap.clear(); }

TransactionList::TransactionList(const transactionMap& txBase) { if (txMap.empty()) { txMap = txBase; } else { for (std::pair<unsigned char*, TransactionBase> tm : txBase) { txMap.insert(tm); } } }

void TransactionList::add(const TransactionBase *tx) { txMap.insert(std::pair<unsigned char*, TransactionBase>(tx->txHash, *tx)); }
