#pragma once

#include"TransactionUtility.h"
#include<string>
#include<string.h>
#include<cstring>

void TransactionUtility::TxUtil::getTime(unsigned char* &src) {

	//unsigned char* time = new unsigned char[18]{ 0 };

	SYSTEMTIME utc;
	SYSTEMTIME cur_time;
	TIME_ZONE_INFORMATION tzi;
	GetSystemTime(&utc);
	GetTimeZoneInformation(&tzi);
	SystemTimeToTzSpecificLocalTime(&tzi, &utc, &cur_time);

	unsigned char* year = new unsigned char[4]{ 0 };
	unsigned char* month = new unsigned char[2]{ 0 };
	unsigned char* day = new unsigned char[2]{ 0 };
	unsigned char* hour = new unsigned char[2]{ 0 };
	unsigned char* min = new unsigned char[2]{ 0 };
	unsigned char* sec = new unsigned char[2]{ 0 };
	unsigned char* milsec = new unsigned char[4]{ 0 };

	_itoa_s((__int16)cur_time.wYear, (char*)year, _msize(year) + 1, 10);
	_itoa_s((__int16)cur_time.wMonth, (char*)month, _msize(month) + 1, 10);
	_itoa_s((__int16)cur_time.wDay, (char*)day, _msize(day) + 1, 10);
	_itoa_s((__int16)cur_time.wHour, (char*)hour, _msize(hour) + 1, 10);
	_itoa_s((__int16)cur_time.wMinute, (char*)min, _msize(min) + 1, 10);
	_itoa_s((__int16)cur_time.wSecond, (char*)sec, _msize(sec) + 1, 10);
	_itoa_s((__int16)cur_time.wMilliseconds, (char*)milsec, _msize(milsec) + 1, 10);

	TransactionUtility::TxUtil::add(src, year);
	TransactionUtility::TxUtil::add(src, month);
	TransactionUtility::TxUtil::add(src, day);
	TransactionUtility::TxUtil::add(src, hour);
	TransactionUtility::TxUtil::add(src, min);
	TransactionUtility::TxUtil::add(src, sec);
	TransactionUtility::TxUtil::add(src, milsec);

	delete[]milsec;
	delete[]sec;
	delete[]min;
	delete[]hour;
	delete[]day;
	delete[]month;
	delete[]year;
}

void TransactionUtility::TxUtil::calculateHash(unsigned char* &hash, unsigned char * addr, unsigned char * val, unsigned char * nonce, unsigned char * cont, unsigned char * time)
{
	std::string digest;
	CryptoPP::SHA256 sha256;

	TransactionUtility::TxUtil::add(hash, addr);
	TransactionUtility::TxUtil::add(hash, val);
	TransactionUtility::TxUtil::add(hash, nonce);
	TransactionUtility::TxUtil::add(hash, cont);
	TransactionUtility::TxUtil::add(hash, time);

	CryptoPP::StringSource *s = new CryptoPP::StringSource((const char*)hash, true, new CryptoPP::HashFilter(sha256, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));

	TransactionUtility::TxUtil::replace(hash, (unsigned char*)digest.c_str());

	delete[] s;
}

void TransactionUtility::TxUtil::calculateHash(unsigned char *& blockHash, unsigned char * hashPrevBlock, unsigned char * merkleRoot, unsigned char * time, unsigned int difficulty, unsigned int nonce)
{
	std::string digest;
	CryptoPP::SHA256 sha256;

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
	unsigned char * strSrc = new unsigned char[src_cnt] { 0 };

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
