
#include"wallet.h"

//Wallet::Wallet() {
//	if (keyPairsAndBalance.size() == 0)geneKey();
//}

void Wallet::geneKey() {
	if (Wallet::GetInstance()->keyPairsAndBalance.size() != 0) {
		printf("you have already key pair\nyou make only one key pair in your wallet\n");
	}
	else {
		WalletData wd;
		CryptoPP::AutoSeededRandomPool prng;
		CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA1>::PrivateKey privKey;
		privKey.Initialize(prng, CryptoPP::ASN1::secp160r1());
		CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA1>::PublicKey pubKey;
		privKey.MakePublicKey(pubKey);

		bool rPrivKey = privKey.Validate(prng, 3);
		bool rPubKey = pubKey.Validate(prng, 3);
		if (!rPrivKey || !rPubKey)printf("Failed generate Key, Please re-generate Key");
		else { wd.privKey = privKey; wd.pubKey = pubKey; }

		wd.balance = 100.0;

		GetInstance()->keyPairsAndBalance.push_back(wd);
		printf("generated new Key\n");
	}
}

void Wallet::save()
{
	std::string fname;
	unsigned __int16 cnt = 1;
	for (WalletData data : GetInstance()->keyPairsAndBalance) {
		fname = "private" + std::to_string(cnt).append(".ec.der");
		CryptoPP::FileSink fs(fname.c_str(), true);
		this->GetInstance()->keyPairsAndBalance.front().privKey.Save(fs);
		cnt++;
	}
}

void Wallet::load()
{
	CryptoPP::FileSource fs("*.ec.der", true);
	WalletData wd;
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA1>::PrivateKey privKey;
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA1>::PublicKey pubKey;
	privKey.Load(fs);
	wd.privKey = privKey;
	privKey.MakePublicKey(pubKey);
	wd.pubKey = pubKey;
	this->GetInstance()->keyPairsAndBalance.push_back(wd);
}

void Wallet::signer(std::string & signature, std::string & message, const std::vector<WalletData>& keysBalance)
{
	Wallet::signer(signature, message, keysBalance.front().privKey);
}

void Wallet::signer(std::string & signature, std::string &message, const WalletData &wd)
{
	Wallet::signer(signature, message, wd.privKey);
}

void Wallet::signer(std::string & signature, std::string &message, const CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA1>::PrivateKey &privateKey)
{
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA1>::Signer signer(privateKey);
	CryptoPP::AutoSeededRandomPool prng;

	CryptoPP::StringSource s(message, true, new CryptoPP::SignerFilter(prng, signer, new CryptoPP::StringSink(signature)));
}

void Wallet::verifier(std::string &signature, std::string &message, const CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA1>::PublicKey &pubKey)
{
	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA1>::Verifier verifier(pubKey);

	bool result = false;

	CryptoPP::StringSource s(signature + message, true, new CryptoPP::SignatureVerificationFilter(verifier, new CryptoPP::ArraySink((CryptoPP::byte*)&result, sizeof(result))));

	if (!result)printf("Failed verify signature");
}

void Wallet::makeRawTransaction(const char* toAddr, const char* value, const char* fee)
{
	list->add(new TransactionBase(toAddr, value, fee, nullptr));
}

void Wallet::signTransaction(TransactionBase & tx, const CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA1>::PrivateKey &privKey)
{
	TransactionUtility::TxUtil util;
	//TransactionBase *tempTx = &tx;
	std::string signature;
	std::string message = "";
	unsigned char* msg = nullptr;
	util.add(msg, tx.txToAddr);
	util.add(msg, tx.txVal);
	util.add(msg, tx.txFee);
	util.add(msg, tx.txTime);
	message.assign((const char*)msg);
	Wallet::signer(signature, message, privKey);
	char* ss = new char[42]{ 0 };
	int i = 0;
	for (char c : signature) {
		ss[i] = c;
		i++;
	}
	tx = TransactionBase((const char*)tx.txToAddr, (const char*)tx.txVal, (const char*)tx.txFee, ss);
	tx.txSigned();

	//delete tempTx;

}

void Wallet::privatekeyHexEncoding(std::string & str, const CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA1>::PrivateKey & privateKey)
{
	const CryptoPP::Integer key = privateKey.GetPrivateExponent();
	std::stringstream ss;
	ss << std::hex << key;
	str = ss.str();
}

void Wallet::publickeyHexEncoding(std::string & str, const CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA1>::PublicKey & publicKey)
{
	const CryptoPP::ECP::Point &pk = publicKey.GetPublicElement();
	const CryptoPP::Integer &pkx = pk.x;
	const CryptoPP::Integer &pky = pk.y;

	std::stringstream ss;
	ss << std::hex << pkx << pky;
	str = ss.str();
}

//int main(void) {
//
//	__wallet_main();
//
//	system("pause");
//	return 0;
//}