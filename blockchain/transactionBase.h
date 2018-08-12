#pragma once

#include"TransactionUtility.h"

class TransactionBase {
public:
	unsigned char * txHash;
	unsigned char * txToAddr;
	unsigned char * txVal;
	unsigned char * txFee;
	unsigned char * txSignedMsg;//signature
	unsigned char * txTime;
	bool txSign = false;

	//std::string msg;
	//public key

public:
	TransactionBase();
	TransactionBase(const TransactionBase&);
	TransactionBase(const char* txToAddr, const char* txVal, const char* txFee, const char* txSignedMsg);
	void setNull();
	TransactionBase getTransactionBase();
	void setTransactionBase(const TransactionBase&);
	void txSigned();

};

