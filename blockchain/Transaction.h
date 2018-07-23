
#include<ctime>
#include<string>

class TransactionData {
public :
	unsigned char* hash;
	bool state_sign;
	unsigned char* toAddress;
	unsigned int value;
	unsigned int nonce;
	unsigned char* data;
	unsigned int time;

};

class Transaction: public TransactionData {
public :

	Transaction();
	Transaction(const TransactionData&);
	void inputTransaction(const TransactionData&);
	void inputTransaction(const unsigned char& ,const bool& ,const unsigned char& ,const unsigned int& ,const unsigned int& ,const unsigned char&/*, const unsigned int&*/ );
	void sign_Transaction();
	void getHash(const Transaction&);
	void setNull();
	Transaction getTransaction();
	
};

Transaction::Transaction() {
	setNull();
}

Transaction::Transaction(const TransactionData &TxData) {
	hash = TxData.hash;
	state_sign = TxData.state_sign;
	toAddress = TxData.toAddress;
	value = TxData.value;
	nonce = TxData.nonce;
	data = TxData.data;
	time = TxData.time;
}

void Transaction::setNull() {
	hash = 0;
	state_sign = 0;
	toAddress = 0;
	value = 0;
	nonce = 0;
	data = 0;
	time = std::time(0);
}
void Transaction::inputTransaction(const TransactionData &TxData) {
	this->hash = TxData.hash;
	this->state_sign = TxData.state_sign;
	this->toAddress = TxData.toAddress;
	this->value = TxData.value;
	this->nonce = TxData.nonce;
	this->data = TxData.data;
	//this->time = TxData.time;
}

void Transaction::inputTransaction(const unsigned char&hash, const bool &state_sign, const unsigned char &toAddress, const unsigned int &value, const unsigned int &nonce, const unsigned char &data/*, const unsigned int &time*/)
{
	*this->hash = hash;
	this->state_sign = state_sign;
	*this->toAddress = toAddress;
	this->value = value;
	this->nonce = nonce;
	*this->data = data;
	//this->time = time;

}