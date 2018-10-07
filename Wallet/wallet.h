
//#pragma comment(lib, "../../../cryptopp700/Win32/Output/Release/cryptlib.lib")
#include"eccrypto.h"
#include"osrng.h"
#include"oids.h"
#include"filters.h"
#include"files.h"
#include"hex.h"
#include"transactionList.h"
#include"sstream"

#pragma once

using namespace std;
using namespace CryptoPP;


typedef ECDSA<ECP, SHA1>::PrivateKey PRIVATEKEY;
typedef ECDSA<ECP, SHA1>::PublicKey PUBLICKEY;
typedef ECDSA<ECP, SHA1>::Signer SIGNER;
typedef ECDSA<ECP, SHA1>::Verifier VERIFIER;

typedef struct KEYPAIR {
	PRIVATEKEY privKey;
	PUBLICKEY pubKey;

	KEYPAIR(const PRIVATEKEY& privKey, const PUBLICKEY& pubKey) :privKey(privKey), pubKey(pubKey) {};
	bool operator==(const KEYPAIR& kp) const
	{
		return privKey.GetPrivateExponent() == kp.privKey.GetPrivateExponent();
	}
	bool operator==(const PRIVATEKEY& pvKey) const
	{
		return privKey.GetPrivateExponent() == privKey.GetPrivateExponent();
	}
}KP;

//use static local singleton pattern
class Wallet {
private:
	Wallet() {};
	~Wallet() {};
public:
	float balance = 100;
	vector<KP> keys;
	TransactionList *list = TransactionList::GetInstance();

	static Wallet* GetInstance() { static Wallet wallet; return &wallet; }
	void geneKey();
	void save(const PRIVATEKEY& privKey, const string& fname);
	void save(const PRIVATEKEY& privKey);
	void saveAll(const string& fname);
	void saveAll();
	void load();
	void signer(string &signature,const string &message, const PRIVATEKEY& privKey);
	void verifier(const string &signature,const string &message, const PUBLICKEY &publicKey);
	void makeRawTransaction(const char* toAddr, const char* value, const char* fee);
	void signTransaction(TransactionBase & tx, const PRIVATEKEY &privKey);
	void privatekeyHexEncoding(string &str, const PRIVATEKEY &privateKey);
	string privatekeyHexEncoding(const PRIVATEKEY &privateKey);
	void publickeyHexEncoding(string &str, const PUBLICKEY &publicKey);
	string publickeyHexEncoding(const PUBLICKEY &publicKey);
};
