
#include<time.h>

//Tx �־�� �� �� : nonce, Value, toAddress, transaction, signature, transaction hash, prev transaction hash, include block
//essential functions : signature function



class TransactionDataStructure {
public :
	unsigned char* prevTxHash;
	//unsigned char* includedBlock;//�����غ��߾� ��
	unsigned char* hash;
	unsigned int nonce;
	unsigned int value;
	unsigned char* toAddress;
	unsigned int transactionTime;
	bool signedTx;
};

class Transaction:public TransactionDataStructure {
public :
	void setNull();
	Transaction();
	Transaction(TransactionDataStructure);
	void signTransaction(TransactionDataStructure);
	bool isPrevTransaction();
	unsigned char* prevTransactionHash();

};

Transaction::Transaction() {
	setNull();
}

Transaction::Transaction(TransactionDataStructure TxDataStructure) {
	prevTxHash = TxDataStructure.prevTxHash;
	hash = TxDataStructure.hash;
	nonce = TxDataStructure.nonce;
	value = TxDataStructure.value;
	toAddress = TxDataStructure.toAddress;
	transactionTime = TxDataStructure.transactionTime;
	signedTx = TxDataStructure.signedTx;
}

void Transaction::setNull() {
	prevTxHash = 0;//prev hash �� ���ؼ� �ֱ�
	hash = 0;
	nonce = 0;
	value = 0;  
	toAddress = 0;
	transactionTime  = time(0);
	signedTx = 0;
};


