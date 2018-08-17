#pragma once

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

	TransactionUtility::TxUtil::replace(src, (unsigned char*)str.c_str());

}

void TransactionUtility::TxUtil::calculateHash(unsigned char* &hash, unsigned char * addr, unsigned char * val, unsigned char * fee, unsigned char * sMsg, unsigned char * time)
{
	std::string digest;
	CryptoPP::SHA256 sha256;

	//std::string temp;
	//temp.append((const char*)addr).append((const char*)val).append((const char*)fee).append((const char*)sMsg).append((const char*)time);

	TransactionUtility::TxUtil::add(hash, addr);
	TransactionUtility::TxUtil::add(hash, val);
	TransactionUtility::TxUtil::add(hash, fee);
	TransactionUtility::TxUtil::add(hash, sMsg);
	TransactionUtility::TxUtil::add(hash, time);

	CryptoPP::StringSource *s = new CryptoPP::StringSource((const char*)hash, true, new CryptoPP::HashFilter(sha256, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));

	TransactionUtility::TxUtil::replace(hash, (unsigned char*)digest.c_str());

	delete[] s;
}

void TransactionUtility::TxUtil::calculateHash(unsigned char *& blockHash, unsigned char * hashPrevBlock, unsigned char * merkleRoot, unsigned char * time, unsigned int difficulty, unsigned int nonce)
{
	std::string digest;
	CryptoPP::SHA256 sha256;
	//std::string temp((char*) blockHash);

	//temp.append((const char*)hashPrevBlock).append((const char*)merkleRoot).append((const char*)time).append((const char*)difficulty).append((const char*)nonce);


	TransactionUtility::TxUtil::add(blockHash, hashPrevBlock);
	TransactionUtility::TxUtil::add(blockHash, merkleRoot);
	TransactionUtility::TxUtil::add(blockHash, time);
	TransactionUtility::TxUtil::add(blockHash, difficulty);
	TransactionUtility::TxUtil::add(blockHash, nonce);

	CryptoPP::StringSource *s = new CryptoPP::StringSource((const char*)blockHash, true, new CryptoPP::HashFilter(sha256, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));

	TransactionUtility::TxUtil::replace(blockHash, (unsigned char*)digest.c_str());

	delete[] s;
}

void TransactionUtility::TxUtil::calculateHash(unsigned char* & src) {
	CryptoPP::SHA256 sha256;
	std::string digest;

	CryptoPP::StringSource *s = new CryptoPP::StringSource((const char*)src, true, new CryptoPP::HashFilter(sha256, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));

	TransactionUtility::TxUtil::replace(src, (unsigned char*)digest.c_str());

	delete[] s;
}

void TransactionUtility::TxUtil::add(unsigned char* &dest, unsigned char* src) {

	int i = 0;
	int dest_cnt = 0;
	int src_cnt = 0;


	if (dest != nullptr && src != nullptr) {
		unsigned char * temp = dest;

		while (true) {
			if (dest[i] == '\0')break;
			else
			{
				dest_cnt++;
			}
			i++;
		}
		i = 0;
		while (true) {
			if (src[i] == '\0')break;
			else
			{
				src_cnt++;
			}
			i++;
		}
		dest = new unsigned char[dest_cnt + src_cnt + 1]{ 0 };
		for (int j = 0; j < dest_cnt; j++) {
			dest[j] = temp[j];
		}

		for (i = 0; i < dest_cnt + src_cnt + 1; i++)
		{
			if (src[i] == '\0') { dest[dest_cnt + i] = '\0'; break; }
			else {
				dest[dest_cnt + i] = src[i];
			}
		}

		delete[] temp;
	}
	else if (dest == nullptr && src == nullptr) {
		//pass
	}
	else if (dest == nullptr) {
		i = 0;
		while (true) {
			if (src[i] == '\0')break;
			else
			{
				src_cnt++;
			}
			i++;
		}
		dest = new unsigned char[src_cnt + 1]{ 0 };
		for (int i = 0; i < src_cnt + 1; i++)
		{
			if (src[i] == '\0') { dest[i] = '\0'; break; }
			else {
				dest[i] = src[i];
			}
		}
	}
}

void TransactionUtility::TxUtil::add(unsigned char *& dest, unsigned int src)
{
	int i = 0;
	int dest_cnt = 0;
	int src_cnt = (src / 10) + 1;
	unsigned char * strSrc = new unsigned char[_msize(dest)+1] {0};

	if (dest != nullptr) {
		unsigned char* temp = dest;

		while (true) {
			if (dest[i] == '\0')break;
			else
			{
				dest_cnt++;
			}
			i++;
		}
		_itoa_s(src, (char*)strSrc, _msize(strSrc) + 1, 10);
		dest = new unsigned char[dest_cnt + src_cnt + 1]{ 0 };
		for (int j = 0; j < dest_cnt; j++) {
			dest[j] = temp[j];
		}

		i = 0;
		for (int i = 0; i < dest_cnt + src_cnt + 1; i++)
		{
			if (strSrc[i] == '\0') { dest[dest_cnt + i] = '\0'; break; }
			else {
				dest[dest_cnt + i] = strSrc[i];
			}
		}
		delete[] temp;

	}
	else if (dest == nullptr) {

		_itoa_s(src, (char*)strSrc, _msize(strSrc) + 1, 10);
		dest = new unsigned char[src_cnt + 1]{ 0 };
		i = 0;
		for (int i = 0; i < src_cnt + 1; i++)
		{
			if (strSrc[i] == '\0') { dest[i] = '\0'; break; }
			else {
				dest[i] = strSrc[i];
			}
		}

	}
	strSrc = { 0 };
	delete[] strSrc;
}

void TransactionUtility::TxUtil::replace(unsigned char *& dest, unsigned char *src)
{
	unsigned char* temp = dest;

	dest = new unsigned char[_msize(src)]{ 0 };

	int i = 0;
	while (true) {
		if (src[i] == '\0') { dest[i] = '\0'; break; }
		else {
			dest[i] = src[i];
		}
		i++;
	}
	delete[] temp;

}
