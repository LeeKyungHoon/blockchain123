#pragma once

#include"TransactionUtility.h"

class TransactionBase {
public:
	unsigned char * txHash;
	unsigned char * txToAddr;
	unsigned char * txVal;
	unsigned char * txNonce;
	unsigned char * txCont;
	unsigned char * txTime;

public:
	inline TransactionBase();
	inline TransactionBase(const TransactionBase&);
	inline TransactionBase(const char* , const char* , const char* , const char* );
	void setNull();
	TransactionBase getTransactionBase();
	void setTransactionBase(const TransactionBase&);

};

