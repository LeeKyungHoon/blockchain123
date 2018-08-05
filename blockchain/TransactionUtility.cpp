#pragma once

#include"TransactionUtility.h"
#include<string>
#include<string.h>
#include<cstring>

void TransactionUtility::TxUtil::getTime(unsigned char* &src) {

	unsigned char* time = new unsigned char[18]{ 0 };

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

	TransactionUtility::TxUtil::add(time, year);
	TransactionUtility::TxUtil::add(time, month);
	TransactionUtility::TxUtil::add(time, day);
	TransactionUtility::TxUtil::add(time, hour);
	TransactionUtility::TxUtil::add(time, min);
	TransactionUtility::TxUtil::add(time, sec);
	TransactionUtility::TxUtil::add(time, milsec);

	//memcpy_s(src, sizeof(*src), time, _msize(time));
	src = (unsigned char*)"";
	add(src, time);
	delete[]milsec;
	delete[]sec;
	delete[]min;
	delete[]hour;
	delete[]day;
	delete[]month;
	delete[]year;
	//time = { 0 };
	//delete[]time;
}

void TransactionUtility::TxUtil::calculateHash(unsigned char* &hash, unsigned char * addr, unsigned char * val, unsigned char * nonce, unsigned char * cont, unsigned char * time)
{
	unsigned char * str = new unsigned char[64]{ 0 };
	std::string digest;
	CryptoPP::SHA256 sha256;

	TransactionUtility::TxUtil::add(str, addr);
	TransactionUtility::TxUtil::add(str, val);
	TransactionUtility::TxUtil::add(str, nonce);
	TransactionUtility::TxUtil::add(str, cont);
	TransactionUtility::TxUtil::add(str, time);

	CryptoPP::StringSource *s = new CryptoPP::StringSource((const char*)str, true, new CryptoPP::HashFilter(sha256, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));

	add(hash, (unsigned char*)digest.c_str());


	delete[] s;
	//delete[] str;
}

void TransactionUtility::TxUtil::calculateHash(unsigned char *& blockHash, unsigned char * hashPrevBlock, unsigned char * merkleRoot, unsigned char * time, unsigned int difficulty, unsigned int nonce)
{
	unsigned char * str = new unsigned char[64]{ 0 };
	std::string digest;
	CryptoPP::SHA256 sha256;

	TransactionUtility::TxUtil::add(str, blockHash);
	TransactionUtility::TxUtil::add(str, hashPrevBlock);
	TransactionUtility::TxUtil::add(str, merkleRoot);
	TransactionUtility::TxUtil::add(str, time);
	TransactionUtility::TxUtil::add(str, difficulty);
	TransactionUtility::TxUtil::add(str, nonce);

	CryptoPP::StringSource *s = new CryptoPP::StringSource((const char*)str, true, new CryptoPP::HashFilter(sha256, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));

	blockHash = (unsigned char*)"";
	add(blockHash, (unsigned char*)digest.c_str());


	delete[] s;
	//delete[] str;
}

void TransactionUtility::TxUtil::calculateHash(unsigned char* & src) {
	CryptoPP::SHA256 sha256;
	std::string digest;

	CryptoPP::StringSource *s = new CryptoPP::StringSource((const char*)src, true, new CryptoPP::HashFilter(sha256, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));

	src = (unsigned char*)"";
	add(src, (unsigned char*)digest.c_str());


	delete[] s;
}

void TransactionUtility::TxUtil::add(unsigned char* &dest, unsigned char* src) {

	int i = 0;
	int dest_cnt = 0;
	int src_cnt = 0;

	if (dest != nullptr && src != nullptr) {

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
		unsigned char * temp = new unsigned char[dest_cnt + src_cnt + 1]{ 0 };
		for (int j = 0; j < dest_cnt; j++) {
			temp[j] = dest[j];
		}

		i = 0;
		for (int i = 0; i < dest_cnt + src_cnt + 1; i++)
		{
			if (src[i] == '\0') { temp[dest_cnt + i] = '\0'; break; }
			else {
				temp[dest_cnt + i] = src[i];
			}
		}

		dest = temp;

		//delete[] temp;
	}
}

void TransactionUtility::TxUtil::add(unsigned char *& dest, unsigned int src)
{

	int i = 0;
	int dest_cnt = 0;
	int src_cnt = (src / 10) + 1;
	unsigned char * strSrc = new unsigned char[src_cnt] { 0 };

	if (dest != nullptr) {

		while (true) {
			if (dest[i] == '\0')break;
			else
			{
				dest_cnt++;
			}
			i++;
		}
		_itoa_s(src, (char*)strSrc, _msize(strSrc) + 1, 10);
		unsigned char * temp = new unsigned char[dest_cnt + src_cnt + 1]{ 0 };
		for (int j = 0; j < dest_cnt; j++) {
			temp[j] = dest[j];
		}

		i = 0;
		for (int i = 0; i < dest_cnt + src_cnt + 1; i++)
		{
			if (strSrc[i] == '\0') { temp[dest_cnt + i] = '\0'; break; }
			else {
				temp[dest_cnt + i] = strSrc[i];
			}
		}
		dest = temp;

		delete[] temp;
	}

	delete[] strSrc;

}
