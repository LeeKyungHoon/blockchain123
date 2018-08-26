
#include"TransactionUtility.h"
#include<string>
#include<string.h>
#include<cstring>

void TransactionUtility::TxUtil::getTime(unsigned char* &src) {

	SYSTEMTIME utc;
	SYSTEMTIME cur_time;
	TIME_ZONE_INFORMATION tzi;
	GetSystemTime(&utc);
	GetTimeZoneInformation(&tzi);
	SystemTimeToTzSpecificLocalTime(&tzi, &utc, &cur_time);

	std::string year = std::to_string(cur_time.wYear);
	std::string month = std::to_string(cur_time.wMonth);
	std::string day = std::to_string(cur_time.wDay);
	std::string hour = std::to_string(cur_time.wHour);
	std::string min = std::to_string(cur_time.wMinute);
	std::string sec = std::to_string(cur_time.wSecond);
	std::string milsec = std::to_string(cur_time.wMilliseconds);

	std::string str;

	str.append(year).append(month).append(day).append(hour).append(min).append(sec).append(milsec);

	memcpy_s(src, _msize(src), str.c_str(), strlen(str.c_str()));
}

void TransactionUtility::TxUtil::calculateHash(unsigned char* &hash, unsigned char * addr, unsigned char * val, unsigned char * fee, unsigned char * sMsg, unsigned char * time)
{
	std::string digest;
	CryptoPP::SHA256 sha256;
	std::string input;
	//byte digest[CryptoPP::SHA256::DIGESTSIZE];

	input.append((const char*)hash).append((const char*)addr).append((const char*)val).append((const char*)fee).append((const char*)sMsg).append((const char*)time);

	CryptoPP::StringSource ss(input, true, new CryptoPP::HashFilter(sha256, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));

	memcpy_s(hash, _msize(hash), digest.c_str(), strlen(digest.c_str()));


}

void TransactionUtility::TxUtil::calculateHash(unsigned char *& blockHash, unsigned char * hashPrevBlock, unsigned char * merkleRoot, unsigned char * time, unsigned int difficulty, unsigned int nonce)
{
	CryptoPP::SHA256 sha256;
	std::string digest;
	std::string input;

	input.append((const char*)blockHash).append((const char*)hashPrevBlock).append((const char*)merkleRoot).append((const char*)time).append(std::to_string(difficulty)).append(std::to_string(nonce));

	CryptoPP::StringSource ss(input, true, new CryptoPP::HashFilter(sha256, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));

	memcpy_s(blockHash, _msize(blockHash), digest.c_str(), strlen(digest.c_str()));


}



void TransactionUtility::TxUtil::calculateHash(unsigned char* & src) {
	CryptoPP::SHA256 sha256;
	std::string input;
	std::string digest;
	input.append((const char*)src);

	CryptoPP::StringSource ss(input, true, new CryptoPP::HashFilter(sha256, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));

	memcpy_s(src, _msize(src), digest.c_str(), strlen(digest.c_str()));
}



void TransactionUtility::TxUtil::add(unsigned char* &dest, unsigned char* src) {

	int dest_cnt = charCount(dest);
	int src_cnt = charCount(src);

	for (int i = 0; i < src_cnt; i++) {
		dest[dest_cnt + i] = src[i];
	}
	dest[dest_cnt + src_cnt] = '\0';

}

int TransactionUtility::TxUtil::charCount(unsigned char * str)
{
	int i = 0;
	int cnt = 0;
	while (true) {
		if (str == nullptr) { break; }
		else if (str[i] == '\0') { break; }
		else {
			cnt += 1;
			i += 1;
		}
	}

	return cnt;
}

