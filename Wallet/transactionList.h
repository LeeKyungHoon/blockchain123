#pragma once

#include"transactionBase.h"
#include<unordered_map>
#include<map>

using namespace std;

class TransactionList : public TransactionBase {
private:
	unordered_map<PUCHAR, TransactionBase> txMap;
	TransactionList() {};
	~TransactionList() {};
public:
	static TransactionList* GetInstance() { static TransactionList txList; return &txList; };
	void listConstructor(const unordered_map<PUCHAR, TransactionBase>& list) {
		if (!txMap.empty()) {
			txMap.clear();
		}
		for (pair<PUCHAR, TransactionBase> p : list) {
			txMap.insert(p);
		}
	};
	void listConstructor(const TransactionList & list) {
		if (!txMap.empty()) {
			txMap.clear();
		}
		for (pair<PUCHAR, TransactionBase> p : list.txMap) {
			txMap.insert(p);
		}
	};
	void add(const TransactionBase & tx) {
		txMap.insert(pair<PUCHAR, TransactionBase>(tx.txHash, tx));
	};
	void add(const PUCHAR& hash, const TransactionBase& t) {
		txMap.insert(pair < PUCHAR, TransactionBase>(hash, t));
	};
	void add(const unordered_map<PUCHAR, TransactionBase> & list) {
		for (auto a : list) {
			txMap.insert(a);
		}
	};
	TransactionBase getLastValue() {
		TransactionBase t;

		for (auto a = txMap.begin(); a != txMap.end(); ++a) {
			if (next(a) == txMap.end()) {
				t = a->second;
			}
		}

		return t;
	};
	pair<PUCHAR, TransactionBase> getLastElem() {
		pair<PUCHAR, TransactionBase> t;
		for (auto a = txMap.begin(); a != txMap.end(); ++a) {
			if (next(a) == txMap.end()) {
				t = pair<PUCHAR, TransactionBase>(a->first, a->second);
			}
		}
		return t;
	};
	unordered_map<PUCHAR, TransactionBase> getTransactions() {
		return txMap;
	}
	pair<PUCHAR, TransactionBase> getElem(const PUCHAR& key) {
		if (txMap.find(key) == txMap.end()) {
			printf("해당 키가 없습니다\n");
		}else{
			return pair<PUCHAR, TransactionBase>(key, txMap.at(key));
		}
	}
	TransactionBase getValue(const PUCHAR& key) {
		if (txMap.find(key) == txMap.end()) {
			printf("해당 키가 없습니다\n");
		}
		else {
			return txMap.at(key);
		}
	}

	unordered_map<PUCHAR, TransactionBase> getList() {
		return this->txMap;
	}

};
