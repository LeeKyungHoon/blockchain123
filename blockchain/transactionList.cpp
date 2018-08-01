
#include"transactionList.h"

TransactionList::TransactionList() {

}

TransactionList::TransactionList(const transactionMap& txBase) {
	if (txMap.empty()) {
		txMap = txBase;
	}
	else {
		for (std::pair<unsigned char*, TransactionBase> tm : txBase) {
			txMap.insert(tm);
		}
	}

}

void TransactionList::add(const TransactionBase *tx) {
	txMap.insert(std::pair<unsigned char*, TransactionBase>(tx->txHash, *tx));
}


//int main() {
//	TransactionBase *t1 = new TransactionBase("100", "100", "100", "100");
//	TransactionBase *t2 = new TransactionBase("200", "200", "200", "200");
//	TransactionBase t3 = TransactionBase("300", "300", "300", "300");
//
//	TransactionList tL;
//
//	tL.add(t1);
//	tL.add(t2);
//	tL.add(&t3);
//
//	for (std::pair<unsigned char*, TransactionBase> map : tL.txMap) {
//		printf("map stored hash : %s\n txHash : %s\n txAddr : %s\n txVal : %s\n txNonce : %s\n txCont : %s\n txTime : %s\n", map.first, map.second.txHash,map.second.txToAddr, map.second.txVal, map.second.txNonce,map.second.txCont,map.second.txTime);
//	}
//	system("pause");
//
//	return 0;
//}