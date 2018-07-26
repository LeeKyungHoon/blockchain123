//#include"Transaction.h"
//#include"KISA_SHA256.h"
//#include"TransactionUtility.h"
////#include"cryptopp700/sha.h"
//
//using namespace TransactionUtility;
//
//void Transaction::sign_Transaction() {
//	this->state_sign = true;
//}
//
//unsigned char* Transaction::getHash(const Transaction &Tx ) {
//	std::string txString = "";
//	unsigned char* encryption_txStr = new unsigned char[32];
//	txString.append(std::to_string(Tx.state_sign));
//	txString.append(reinterpret_cast<const char*>(Tx.toAddress));
//	txString.append(std::to_string(Tx.value));
//	txString.append(std::to_string(Tx.nonce));
//	txString.append(reinterpret_cast<const char*>(Tx.data));
//	txString.append(std::to_string(Tx.time));
//	
//	SHA256_Encrpyt((unsigned char*)txString.c_str(), txString.length(), encryption_txStr);
//
//	//CryptoPP::SHA256 calHash;
//	//this->hash = 
//
//	return encryption_txStr;
//}
//
//unsigned char* Transaction::getHash() {
//	TxUtil util;
//	unsigned char* input = new unsigned char[32]{ 0 };
//	unsigned char * encryption_txStr = new unsigned char[32]{0};
//	
//	input = util.addCharP(input,this->state_sign);
//	input = util.addCharP(input, this->toAddress);
//
//	//this->toAddress;
//	//this->value;
//	//this->nonce;
//	//this->data;
//	//this->time;
//	//input = (unsigned char*)"hello";
//
//	/*const unsigned char * test = (unsigned char*)"hello world";
//
//	printf("%p\n", test);*/
//
//	SHA256_Encrpyt(input, 32, encryption_txStr);
//
//	return encryption_txStr;
//
//}
//
////Transaction Transaction::getTransaction() {
////
////	return TransactionData();
////}
//
////int main(void) {
////	//Transaction tx = Transaction(0,0,(unsigned)"hello");
////	//unsigned char * result = tx.getHash();
////
////	//for (int i = 0; i < 32; i++) {
////	//	printf("%02x", result[i]);
////	//};
////
////	//printf("int : %d, string : %s, unsigned char* %s", time(0), time(0),(unsigned char*)time(0));
////	time_t rawtime;
////	struct tm * timeinfo = new tm ;
////	char buffer[80];
////
////	time(&rawtime);
////	localtime_s(timeinfo, &rawtime);
////
////	strftime(buffer, 80, "Now it's %I:%M%p.", timeinfo);
////	puts(buffer);
////
////	system("pause");
////
////	return 0;
////}