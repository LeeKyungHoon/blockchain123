

#include"cryptopp700/eccrypto.h"
#include"cryptopp700/osrng.h"
#include"cryptopp700/oids.h"
#include"cryptopp700/filters.h"
#include"cryptopp700/files.h"
#include"transactionList.h"
#include<sstream>

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
