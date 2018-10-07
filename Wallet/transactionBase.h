#pragma once

#include"TransactionUtility.h"

class TransactionBase : public TransactionUtility::TxUtil {
public:
	PUCHAR txHash;
	PUCHAR txToAddr;
	PUCHAR txVal;
	PUCHAR txFee;
	PUCHAR txSignedMsg;//signature
	PUCHAR txTime;
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
					const char * s_Msg):txToAddr((PUCHAR)toAddr),
										txVal((PUCHAR)val),
										txFee((PUCHAR)fee),
										txSignedMsg((PUCHAR)s_Msg){
		txHash = new UCHAR[128]{ 0 };
		txTime = new UCHAR[128]{ 0 };
		getTime(txTime);
		calculateHash(txHash, txToAddr, txVal, txFee, txSignedMsg, txTime);
	};
	TransactionBase(const char * toAddr,
					const char * val,
					const char * fee) : txToAddr((PUCHAR)toAddr),
										txVal((PUCHAR)val),
										txFee((PUCHAR)fee) {
		txHash = new UCHAR[128]{ 0 };
		txTime = new UCHAR[128]{ 0 };
		txSignedMsg = new UCHAR[128]{ 0 };
		getTime(txTime);
		calculateHash(txHash, txToAddr, txVal, txFee, txSignedMsg, txTime);
	};
	TransactionBase(const char * hash,
					const char * toAddr,
					const char * val,
					const char * fee,
					const char * s_Msg,
					const char * time,
					const char * sign) :txHash((PUCHAR)hash),
										txToAddr((PUCHAR)toAddr),
										txVal((PUCHAR)val),
										txFee((PUCHAR)fee),
										txSignedMsg((PUCHAR)s_Msg),
										txTime((PUCHAR)time) {txSign = ((std::memcmp(sign,"0",1)==0) ? 0 : 1);};

	void setNull() {
		txHash = new UCHAR[128]{ 0 };
		txToAddr = new UCHAR[128]{ 0 };
		txVal = new UCHAR[128]{ 0 };
		txFee = new UCHAR[128]{ 0 };
		txSignedMsg = new UCHAR[128]{ 0 };
		txTime = new UCHAR[128]{ 0 };
	};
	TransactionBase getTransactionBase() { return *this; };
	void insertSignedMsg(const string& signature) { /*for (int i = 0; i < 42; i++) { txSignedMsg[i] = signature[i]; }*/txSignedMsg = (PUCHAR)signature.c_str(); };
	void setTransactionBase(const TransactionBase& txBase) { TransactionBase::TransactionBase(txBase); };
	void txSigned() { txSign = !txSign; };

};

