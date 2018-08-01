
#include"transactionBase.h"
#include<unordered_map>

typedef std::unordered_map<unsigned char*, TransactionBase> transactionMap;

class TransactionList {
public:
	transactionMap txMap;
	TransactionList();
	TransactionList(const transactionMap&);
	void add(const TransactionBase*);
};