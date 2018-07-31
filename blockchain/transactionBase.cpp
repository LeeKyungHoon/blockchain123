#pragma once

#include"transactionBase.h"

inline TransactionBase::TransactionBase() {

	setNull();

}

inline TransactionBase::TransactionBase(const TransactionBase& txBase) {

	setNull();
	txHash = txBase.txHash;
	txToAddr = txBase.txToAddr;
	txVal = txBase.txVal;
	txNonce = txBase.txNonce;
	txCont = txBase.txCont;
	txTime = txBase.txTime;

}

inline TransactionBase::TransactionBase(const char* toAddr, const char* val, const char* nonce, const char* cont)
{
	TransactionUtility::TxUtil util;
	setNull();
	txToAddr = (unsigned char*)toAddr;
	txVal = (unsigned char*)val;
	txNonce = (unsigned char*)nonce;
	txCont = (unsigned char*)cont;
	util.getTime(txTime);
	util.calculateHash(this->txHash,this->txToAddr, this->txVal, this->txNonce, this->txCont, this->txTime);
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

//int main(void) {
//
//	TransactionBase *tx = new TransactionBase("100", "100", "100", "100");
//	printf("hash : %s, addr : %s, val : %s, nonce : %s, cont : %s, time : %s\n", tx->txHash, tx->txToAddr,tx->txVal,tx->txNonce,tx->txCont,tx->txTime);
//
//	system("pause");
//	return 0;
//
//}

