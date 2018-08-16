
//#pragma comment(lib, "../../../cryptopp700/Win32/Output/Release/cryptlib.lib")
#include"eccrypto.h"
#include"osrng.h"
#include"oids.h"
#include"filters.h"
#include"files.h"
#include"transactionList.h"
#include"sstream"
//#include<eccrypto.h>
//#include<osrng.h>
//#include<oids.h>
//#include<filters.h>
//#include<files.h>
//#include"transactionList.h"
//#include<sstream>
struct WalletData
{
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA1>::PrivateKey privKey;
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA1>::PublicKey pubKey;
	float balance = 0;
};

//use static local singleton pattern

class Wallet {
private:
	Wallet() {};
	Wallet(const Wallet& o_wallet);
	~Wallet() {};
public:
	std::vector<WalletData> keyPairsAndBalance;
	TransactionList *list = new TransactionList();
	static Wallet* GetInstance() { static Wallet wallet; return &wallet; }
	void geneKey();
	void save();
	void load();
	void signer(std::string &signature, std::string &message, const std::vector<WalletData> &keysBalance);
	void signer(std::string &signature, std::string &message, const WalletData &wd);
	void signer(std::string &signature, std::string &message, const CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA1>::PrivateKey &privateKey);
	void verifier(std::string &signature, std::string &message, const 	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA1>::PublicKey &publicKey);
	void makeRawTransaction(const char* toAddr, const char* value, const char* fee);
	void signTransaction(TransactionBase & tx, const CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA1>::PrivateKey &privKey);
	void privatekeyHexEncoding(std::string &str, const CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA1>::PrivateKey &privateKey);
	void publickeyHexEncoding(std::string &str, const CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA1>::PublicKey &publicKey);
};
