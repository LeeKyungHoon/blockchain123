#pragma once

#include"transactionBase.h"

TransactionBase::TransactionBase() {
	setNull();
}

TransactionBase::TransactionBase(const TransactionBase& txBase) {

	setNull();
	txHash = txBase.txHash;
	txToAddr = txBase.txToAddr;
	txVal = txBase.txVal;
	txFee = txBase.txFee;
	txSignedMsg = txBase.txSignedMsg;
	txTime = txBase.txTime;

}

TransactionBase::TransactionBase(const char* toAddr, const char* val, const char* fee, const char* sMsg)
{
	TransactionUtility::TxUtil util;
	setNull();
	txToAddr = (unsigned char*)toAddr;
	txVal = (unsigned char*)val;
	txFee = (unsigned char*)fee;
	txSignedMsg = (unsigned char*)sMsg;
	util.getTime(txTime);
	util.calculateHash(this->txHash, this->txToAddr, this->txVal, this->txFee, this->txSignedMsg, this->txTime);
}

void TransactionBase::setTransactionBase(const TransactionBase& txBase) {
	TransactionBase::TransactionBase(txBase);
}

TransactionBase TransactionBase::getTransactionBase() { return *this; }

void TransactionBase::setNull() {

	txHash = nullptr;
	txToAddr = nullptr;
	txVal = nullptr;
	txFee = nullptr;
	txSignedMsg = nullptr;
	txTime = nullptr;
}

void TransactionBase::txSigned() {
	this->txSign = !this->txSign;
}
