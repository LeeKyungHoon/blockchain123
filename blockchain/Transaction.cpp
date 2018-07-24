#include"Transaction.h"
#include"KISA_SHA256.h"
//#include"cryptopp700/sha.h"

void Transaction::sign_Transaction() {
	this->state_sign = true;
}

unsigned char* Transaction::getHash(const Transaction &Tx ) {
	std::string txString = "";
	unsigned char* encryption_txStr = new unsigned char[32];
	txString.append(std::to_string(Tx.state_sign));
	txString.append(reinterpret_cast<const char*>(Tx.toAddress));
	txString.append(std::to_string(Tx.value));
	txString.append(std::to_string(Tx.nonce));
	txString.append(reinterpret_cast<const char*>(Tx.data));
	txString.append(std::to_string(Tx.time));
	
	SHA256_Encrpyt((unsigned char*)txString.c_str(), txString.length(), encryption_txStr);


	//CryptoPP::SHA256 calHash;
	//this->hash = 

	return encryption_txStr;
}

unsigned char* Transaction::getHash() {
	unsigned char* input = new unsigned char[32];
	unsigned char * encryption_txStr = new unsigned char[32];

	input = (unsigned char*)"hello";

	SHA256_Encrpyt(input, 32, encryption_txStr);

	return encryption_txStr;

}


Transaction Transaction::getTransaction() {

	return TransactionData();
}

int main(void) {
	Transaction *tx = new Transaction();
	unsigned char * result = tx->getHash();

	for (int i = 0; i < 32; i++) {
		printf("%02x", result[i]);
	}

	return 0;
}