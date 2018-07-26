#pragma once

#include<string>
#include<chrono>
#include<time.h>
#include<ctime>

class TransactionBase {
public:
	unsigned char * txHash;
	unsigned char * txToAddr;
	unsigned char * txVal;
	unsigned char * txNonce;
	unsigned char * txCont;
	unsigned char * txTime;

public:
	TransactionBase();
	TransactionBase(const TransactionBase&);
	TransactionBase(const char* , const char* , const char* , const char* );
	void setNull();
	TransactionBase getTransactionBase();
	void setTransactionBase(const TransactionBase&);

};
