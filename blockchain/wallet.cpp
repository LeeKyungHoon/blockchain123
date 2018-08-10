
#include"wallet.h"

using namespace CryptoPP;

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
		fname = "private"+ std::to_string(cnt).append("private.ec.der");
		CryptoPP::FileSink fs(fname.c_str(), true);
		this->GetInstance()->keyPairsAndBalance.front().privKey.Save(fs);
		cnt++;
	}
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



int main(void) {

	Wallet * wallet = Wallet::GetInstance();
	wallet->geneKey();

	std::string sign;
	std::string message = "hello world";

	wallet->signer(sign, message, wallet->keyPairsAndBalance.front());

	//
	for (auto a = sign.begin(); a != sign.end(); ++a) {
		printf("%hhx", *a);
	}
	std::cout << std::endl;
	//
	//
	for (auto a = sign.begin(); a != sign.end(); ++a) {
		printf("%x", (*a)&0xff);
		std::cout << std::endl;
	}
	//
	message.append("!");

	wallet->verifier(sign, message, wallet->keyPairsAndBalance.front().pubKey);

	system("pause");
	return 0;

}



















































































//
//#include<iostream>
//#include"cryptopp700/rsa.h"
//#include"cryptopp700/osrng.h"
//#include"cryptopp700/eccrypto.h"
//#include"cryptopp700/oids.h"
//#include"cryptopp700/ripemd.h"
//using namespace CryptoPP::ASN1;
//
//using namespace CryptoPP;
//using namespace std;
//
//
//#include "cryptopp700/files.h"
//using CryptoPP::FileSink;
//using CryptoPP::FileSource;
//
//
//void SaveKey(const RSA::PublicKey& PublicKey, const string& filename)
//{
//	// DER Encode Key - X.509 key format
//	PublicKey.Save(
//		FileSink(filename.c_str(), true /*binary*/).Ref()
//	);
//}
//
//void SaveKey(const RSA::PrivateKey& PrivateKey, const string& filename)
//{
//	// DER Encode Key - PKCS #8 key format
//	PrivateKey.Save(
//		FileSink(filename.c_str(), true /*binary*/).Ref()
//	);
//}
//
//void LoadKey(const string& filename, RSA::PublicKey& PublicKey)
//{
//	// DER Encode Key - X.509 key format
//	PublicKey.Load(
//		FileSource(filename.c_str(), true, NULL, true /*binary*/).Ref()
//	);
//}
//
//void LoadKey(const string& filename, RSA::PrivateKey& PrivateKey)
//{
//	// DER Encode Key - PKCS #8 key format
//	PrivateKey.Load(
//		FileSource(filename.c_str(), true, NULL, true /*binary*/).Ref()
//	);
//}
//
//
//int main(void) {
//	AutoSeededRandomPool rng;
//	InvertibleRSAFunction params;
//	params.GenerateRandomWithKeySize(rng, 3072);
//
//	const Integer& n = params.GetModulus();
//	const Integer& p = params.GetPrime1();
//	const Integer& q = params.GetPrime2();
//	const Integer& d = params.GetPrivateExponent();
//	const Integer& e = params.GetPublicExponent();
//
//	cout << "RSA Parameters:" << endl;
//	cout << " n: " << n << endl;
//	cout << " p: " << p << endl;
//	cout << " q: " << q << endl;
//	cout << " d: " << d << endl;
//	cout << " e: " << e << endl;
//	cout << endl;
//
//	cout << "RSA Parameters Hex:" << endl;
//	cout << " n: " << std::hex << n << endl;
//	cout << " p: " << std::hex << p << endl;
//	cout << " q: " << std::hex << q << endl;
//	cout << " d: " << std::hex << d << endl;
//	cout << " e: " << std::hex << e << endl;
//	cout << endl;
//
//	RSA::PrivateKey privateKeyRSA(params);
//	RSA::PublicKey publicKeyRSA(params);
//
//
//	AutoSeededRandomPool prng;
//	ECDSA<ECP, SHA1>::PrivateKey privateKeyECDSA;
//
//	privateKeyECDSA.Initialize(prng, ASN1::secp160r1());
//	bool result = privateKeyECDSA.Validate(prng, 3);
//
//	if (!result) printf("failed generate privateKey");
//
//	const Integer& x = privateKeyECDSA.GetPrivateExponent();
//	cout << "ECDSA Parameter " << endl;
//	cout << " x: " << std::hex << x << endl;
//	cout << endl;
//
//	ECDSA<ECP, SHA1>::PrivateKey k1;
//	k1.Initialize(prng, secp160r1());
//
//	const Integer& x1 = k1.GetPrivateExponent();
//	cout << "K1: " << std::hex << x1 << endl;
//
//	ByteQueue queue;
//	k1.Save(queue);
//
//	ECDSA<ECP, SHA256>::PrivateKey k2;
//	k2.Load(queue);
//
//	const Integer& x2 = k2.GetPrivateExponent();
//	cout << "K2: " << std::hex << x2 << endl;
//
//	system("pause");
//
//	return 0;
//}
//

