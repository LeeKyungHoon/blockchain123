
#include<iostream>
#include"cryptopp700/rsa.h"
#include"cryptopp700/osrng.h"
#include"cryptopp700/eccrypto.h"
#include"cryptopp700/oids.h"
#include"cryptopp700/ripemd.h"
using namespace CryptoPP::ASN1;

using namespace CryptoPP;
using namespace std;


#include "cryptopp700/files.h"
using CryptoPP::FileSink;
using CryptoPP::FileSource;


void SaveKey(const RSA::PublicKey& PublicKey, const string& filename)
{
	// DER Encode Key - X.509 key format
	PublicKey.Save(
		FileSink(filename.c_str(), true /*binary*/).Ref()
	);
}

void SaveKey(const RSA::PrivateKey& PrivateKey, const string& filename)
{
	// DER Encode Key - PKCS #8 key format
	PrivateKey.Save(
		FileSink(filename.c_str(), true /*binary*/).Ref()
	);
}

void LoadKey(const string& filename, RSA::PublicKey& PublicKey)
{
	// DER Encode Key - X.509 key format
	PublicKey.Load(
		FileSource(filename.c_str(), true, NULL, true /*binary*/).Ref()
	);
}

void LoadKey(const string& filename, RSA::PrivateKey& PrivateKey)
{
	// DER Encode Key - PKCS #8 key format
	PrivateKey.Load(
		FileSource(filename.c_str(), true, NULL, true /*binary*/).Ref()
	);
}


int main(void) {
	AutoSeededRandomPool rng;
	InvertibleRSAFunction params;
	params.GenerateRandomWithKeySize(rng, 3072);

	const Integer& n = params.GetModulus();
	const Integer& p = params.GetPrime1();
	const Integer& q = params.GetPrime2();
	const Integer& d = params.GetPrivateExponent();
	const Integer& e = params.GetPublicExponent();

	cout << "RSA Parameters:" << endl;
	cout << " n: " << n << endl;
	cout << " p: " << p << endl;
	cout << " q: " << q << endl;
	cout << " d: " << d << endl;
	cout << " e: " << e << endl;
	cout << endl;

	cout << "RSA Parameters Hex:" << endl;
	cout << " n: " << std::hex << n << endl;
	cout << " p: " << std::hex << p << endl;
	cout << " q: " << std::hex << q << endl;
	cout << " d: " << std::hex << d << endl;
	cout << " e: " << std::hex << e << endl;
	cout << endl;

	RSA::PrivateKey privateKeyRSA(params);
	RSA::PublicKey publicKeyRSA(params);


	AutoSeededRandomPool prng;
	ECDSA<ECP, SHA1>::PrivateKey privateKeyECDSA;

	privateKeyECDSA.Initialize(prng, ASN1::secp160r1());
	bool result = privateKeyECDSA.Validate(prng, 3);

	if (!result) printf("failed generate privateKey");

	const Integer& x = privateKeyECDSA.GetPrivateExponent();
	cout << "ECDSA Parameter " << endl;
	cout << " x: " << std::hex << x << endl;
	cout << endl;

	ECDSA<ECP, SHA1>::PrivateKey k1;
	k1.Initialize(prng, secp160r1());

	const Integer& x1 = k1.GetPrivateExponent();
	cout << "K1: " << std::hex << x1 << endl;

	ByteQueue queue;
	k1.Save(queue);

	ECDSA<ECP, SHA256>::PrivateKey k2;
	k2.Load(queue);

	const Integer& x2 = k2.GetPrivateExponent();
	cout << "K2: " << std::hex << x2 << endl;

	system("pause");

	return 0;
}

