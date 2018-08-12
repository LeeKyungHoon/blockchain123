
#include"wallet.h"

//Wallet::Wallet() {
//	if (keyPairsAndBalance.size() == 0)geneKey();
//}

void Wallet::geneKey() {
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
}

void Wallet::save()
{
	std::string fname;
	unsigned __int16 cnt = 1;
	for (WalletData data : GetInstance()->keyPairsAndBalance) {
		fname = "private" + std::to_string(cnt).append("private.ec.der");
		CryptoPP::FileSink fs(fname.c_str(), true);
		this->GetInstance()->keyPairsAndBalance.front().privKey.Save(fs);
		cnt++;
	}
}

void Wallet::load()
{
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
	tx = TransactionBase((const char*)tx.txToAddr, (const char*)tx.txVal, (const char*)tx.txFee, signature.c_str());
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

int main(void) {

	Wallet * wallet = Wallet::GetInstance();
	wallet->geneKey();

	std::string privKey;
	std::string pubKey;
	std::string message = "hello world";

	wallet->privatekeyHexEncoding(privKey, wallet->keyPairsAndBalance.front().privKey);
	wallet->publickeyHexEncoding(pubKey, wallet->keyPairsAndBalance.front().pubKey);
	std::cout << privKey << std::endl;
	std::cout << pubKey << std::endl;

	/*const Integer & k1 = wallet->keyPairsAndBalance.front().privKey.GetPrivateExponent();
	std::cout << k1.ByteCount() << std::endl;
	std::cout << k1.GetByte(0) << std::endl;
	std::cout << k1.AbsoluteValue() << std::endl;
	std::cout << k1 << std::endl;
	

	std::stringstream ss;

	ss << std::hex << k1;

	std::string s = ss.str();
	std::cout << std::endl;
	std::cout << s << std::endl;

	const CryptoPP::ECP::Point & q = wallet->keyPairsAndBalance.front().pubKey.GetPublicElement();

	const Integer & qx = q.x;
	const Integer & qy = q.y;

	CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA1>::PublicKey pubkey = wallet->keyPairsAndBalance.front().pubKey;



	std::cout << "pubKey x : " << std::hex << qx << std::endl;
	std::cout << "pubKey y : " << std::hex << qy << std::endl;

*/
	//wallet->makeRawTransaction("abc", "20", "1");

	//wallet->signTransaction(wallet->list->txMap.begin()->second, wallet->keyPairsAndBalance.front().privKey);

	std::string sign;
	wallet->signer(sign, message, wallet->keyPairsAndBalance.front());

	unsigned char* p = new unsigned char[42]{ 0 };

	//std::stringstream ss1;
	//ss1 << std::hex;

	//BYTE tt[42]{ 0 };
	int i = 0;
	for (char c : sign) {
		p[i] = c;
		i++;
	}

	//for (int i = 0; i < sizeof(tt); i++) {
	//	ss1 << (__int32)tt[i];
	//}

	//std::string str1 = ss1.str();


	for (int i = 0; i < 42; i++) {
		printf("%x ", (p[i]) );
	}
	//std::cout << std::endl;
	//std::cout << str1 << std::endl;

	//sign = (const char*)wallet->list->txMap.begin()->second.txSignedMsg;

	//for (int j = 0; j < 160; j++) {
	//	printf("%x", tt[j]);
	//}
	//std::cout << std::endl;
	//std::cout << std::endl;
	////
	//for (auto a = sign.begin(); a != sign.end(); ++a) {
	//	printf("%hhx", *a);
	//}
	//std::cout << std::endl;
	//std::cout << std::endl;
	////
	////
	//for (auto a = sign.begin(); a != sign.end(); ++a) {
	//	printf("%x-", (*a)&0xff);
	//}
	////
	//std::cout << std::endl;
	//std::cout << std::endl;
	////
	//for (auto a = sign.begin(); a != sign.end(); ++a) {
	//	printf("%u  ", *a);
	//}
	////
	//std::cout << std::endl;
	//std::cout << std::endl;
	//for (auto a = sign.begin(); a != sign.end(); ++a) {
	//	printf("%d  ", *a);
	//}
	////
	//std::cout << std::endl;
	//std::cout << std::endl;
	//message.append("!");

	//printf("%s", wallet->list->txMap.begin()->second.txSignedMsg);

	//wallet->verifier(sign, message, wallet->keyPairsAndBalance.front().pubKey);

	system("pause");
	return 0;

}

