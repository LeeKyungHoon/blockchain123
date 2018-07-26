#pragma once

#include"transactionBase.h"
#include"TransactionUtility.h"

TransactionBase::TransactionBase() {

	setNull();

}

TransactionBase::TransactionBase(const TransactionBase& txBase) {

	setNull();
	txHash = txBase.txHash;
	txToAddr = txBase.txToAddr;
	txVal = txBase.txVal;
	txNonce = txBase.txNonce;
	txCont = txBase.txCont;
	txTime = txBase.txTime;

}

TransactionBase::TransactionBase(const char* toAddr, const char* val, const char* nonce, const char* cont)
{
	setNull();
	txToAddr = (unsigned char*)toAddr;
	txVal = (unsigned char*)val;
	txNonce = (unsigned char*)nonce;
	txCont = (unsigned char*)cont;
	txTime = TransactionUtility::TxUtil::getTime();
}

void TransactionBase::setTransactionBase(const TransactionBase& txBase) {
	TransactionBase::TransactionBase(txBase);
}

TransactionBase TransactionBase::getTransactionBase() {

	return *this;

}

void TransactionBase::setNull() {

	txHash = (unsigned char*)"";
	txToAddr = (unsigned char*)"";
	txVal = (unsigned char*)"";
	txNonce = (unsigned char*)"";
	txCont = (unsigned char*)"";
	txTime = (unsigned char*)"";
}
//
//int main(void) {
//
//	TransactionBase *tx = new TransactionBase("100", "100", "100", "100");
//	printf("%s", tx->getTransactionBase().txTime);
//	printf("%d", time(0));
//
//	system("pause");
//	return 0;
//
//}