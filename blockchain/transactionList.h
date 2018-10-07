
#pragma once


#include"transactionBase.h"
#include<unordered_map>

typedef std::unordered_map<unsigned char*, TransactionBase> transactionMap;

class TransactionList {
public:
	transactionMap txMap;
	TransactionList();
	TransactionList(const transactionMap&);
	TransactionList(const TransactionList & list);
	void add(const TransactionBase* tx);
	void add(unsigned char* hash, TransactionBase t);
	TransactionBase getLastElem();
};
