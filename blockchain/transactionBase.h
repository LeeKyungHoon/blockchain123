#pragma once

#include"TransactionUtility.h"
#include"boost/serialization/string.hpp"

class TransactionBase : public TransactionUtility::TxUtil {
public:
	unsigned char * txHash;
	unsigned char * txToAddr;
	unsigned char * txVal;
	unsigned char * txFee;
	unsigned char * txSignedMsg;//signature
	unsigned char * txTime;
	bool txSign = false;

public:
	TransactionBase() { setNull(); };
	TransactionBase(const TransactionBase& txBase) :
		txHash(txBase.txHash),
		txToAddr(txBase.txToAddr),
		txVal(txBase.txVal),
		txFee(txBase.txFee),
		txSignedMsg(txBase.txSignedMsg),
		txTime(txBase.txTime),
		txSign(txBase.txSign) {};
	
	TransactionBase(const char * toAddr,
					const char * val,
					const char * fee,
					const char * s_Msg):txToAddr((unsigned char*)toAddr),
										txVal((unsigned char*)val),
										txFee((unsigned char*)fee),
										txSignedMsg((unsigned char*)s_Msg){
		getTime(txTime);
		calculateHash(txHash, txToAddr, txVal, txFee, txSignedMsg, txTime);

	};
	TransactionBase(const char * hash,
					const char * toAddr,
					const char * val,
					const char * fee,
					const char * s_Msg,
					const char * time,
					const char * sign) :txHash((unsigned char*)hash),
										txToAddr((unsigned char*)toAddr),
										txVal((unsigned char*)val),
										txFee((unsigned char*)fee),
										txSignedMsg((unsigned char*)s_Msg),
										txTime((unsigned char*)time) {txSign = ((std::memcmp(sign,"0",1)==0) ? 0 : 1);};

	void setNull() { txHash = 0;
					 txToAddr = 0;
					 txVal = 0;
					 txFee = 0;
					 txSignedMsg = 0;
					 txTime = 0;
	};
	TransactionBase getTransactionBase() { return *this; };
	void setTransactionBase(const TransactionBase& txBase) { TransactionBase::TransactionBase(txBase); };
	void txSigned() { txSign = !txSign; };

};

