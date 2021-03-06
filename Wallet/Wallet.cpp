
#include"wallet.h"


void Wallet::geneKey() {
	AutoSeededRandomPool prng;
	PRIVATEKEY privKey;
	privKey.Initialize(prng, ASN1::secp160r1());
	PUBLICKEY pubKey;
	privKey.MakePublicKey(pubKey);

	bool rPrivKey = privKey.Validate(prng, 3);
	bool rPubKey = pubKey.Validate(prng, 3);
	if (!rPrivKey || !rPubKey)printf("Failed generate Key, Please re-generate Key");

	keys.push_back(KP(privKey, pubKey));
	printf("generated new Key\n");
}

void Wallet::save(const PRIVATEKEY& privKey, const string& fname)
{
	string name;
	name.assign(fname).append(".ec.der");
	FileSink fs(name.c_str(), true);
	privKey.Save(fs);
}

void Wallet::save(const PRIVATEKEY& privKey) {
	string name;
	privatekeyHexEncoding(name, privKey);
	name.append(".ec.der");
	FileSink fs(name.c_str(), true);
	privKey.Save(fs);
}

void Wallet::saveAll(const string& fname) {
	string name;
	name.assign(fname);
	int cnt = 1;
	for (auto k : keys) {
		name.append(to_string(cnt)).append(".ec.der");
		FileSink fs(name.c_str(), true);
		k.privKey.Save(fs);
	}
}

void Wallet::saveAll() {

	for (auto k : keys) {
		string name;
		privatekeyHexEncoding(name, k.privKey);
		name.append(".ec.der");
		FileSink fs(name.c_str(), true);
		k.privKey.Save(fs);
	}

}

void Wallet::load()
{
	FileSource fs("*.ec.der", true);
	PRIVATEKEY privKey;
	privKey.Load(fs);
	//if (keys.find(privKey) != keys.end()) {
	if (find(keys.begin(), keys.end(), privKey) == keys.end()) {
		printf("already exist key\nPlease load another key");
	}
	else {
		PUBLICKEY pubKey;
		privKey.MakePublicKey(pubKey);
		keys.push_back(KP(privKey, pubKey));
	}
}

void Wallet::signer(string &signature, const string &message, const PRIVATEKEY& privKey)
{
	SIGNER signer(privKey);
	AutoSeededRandomPool prng;

	StringSource s(message, true, new SignerFilter(prng, signer, new StringSink(signature)));
}

void Wallet::verifier(const string &signature, const string &message, const PUBLICKEY &pubKey)
{
	VERIFIER verifier(pubKey);
	bool result = false;
	string temp = signature + message;

	StringSource s(temp, true, new SignatureVerificationFilter(verifier, new ArraySink((byte*)&result, sizeof(result))));

	if (!result)printf("Failed verify signature");
}

void Wallet::makeRawTransaction(const char* toAddr, const char* value, const char* fee)
{
	list->add(TransactionBase(toAddr, value, fee));
}

void Wallet::signTransaction(TransactionBase & tx, const PRIVATEKEY &privKey)
{
	string signature;
	stringstream message;
	message << tx.txToAddr << tx.txVal << tx.txFee << tx.txTime;
	Wallet::signer(signature, message.str(), privKey);
	string str;
	char const hex_chars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

	for (int i = 0; i < signature.length(); ++i)
	{
		char const byte = signature[i];

		str += hex_chars[(byte & 0xF0) >> 4];
		str += hex_chars[(byte & 0x0F) >> 0];
	}
	cout << str << endl;
	memcpy_s(tx.txSignedMsg, _msize(tx.txSignedMsg), str.c_str(), str.length());
	tx.txSigned();


}

void Wallet::privatekeyHexEncoding(string & str, const PRIVATEKEY & privateKey)
{
	const Integer key = privateKey.GetPrivateExponent();
	std::stringstream ss;
	ss << std::hex << key;
	str = ss.str();
}

string Wallet::privatekeyHexEncoding(const PRIVATEKEY & privateKey)
{
	const Integer key = privateKey.GetPrivateExponent();
	std::stringstream ss;
	ss << std::hex << key;

	return ss.str();
}

void Wallet::publickeyHexEncoding(string & str, const PUBLICKEY & publicKey)
{
	const ECP::Point &pk = publicKey.GetPublicElement();
	const Integer &pkx = pk.x;
	const Integer &pky = pk.y;

	std::stringstream ss;
	ss << std::hex << pkx << pky;
	str = ss.str();
}

string Wallet::publickeyHexEncoding(const PUBLICKEY & publicKey)
{
	const ECP::Point &pk = publicKey.GetPublicElement();
	const Integer &pkx = pk.x;
	const Integer &pky = pk.y;
	std::stringstream ss;
	ss << std::hex << pkx << pky;
	
	return ss.str();
}
