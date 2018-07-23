#include"Transaction.h"
#include"cryptopp700/sha.h"

using namespace CryptoPP;

void Transaction::sign_Transaction() {
	this->sign_Transaction = true;
}

void Transaction::getHash(const Transaction &Tx ) {
	std::string txString = "";
	txString.append(std::to_string(Tx.state_sign));

	//this->hash = SHA256::InitState();

}

Transaction Transaction::getTransaction() {

	return TransactionData();
}
