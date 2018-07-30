#pragma once

#include"TransactionUtility.h"

using namespace TransactionUtility;

void TxUtil::getTime(unsigned char* &src) {
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

	TxUtil::add(time,year);
	TxUtil::add(time,month);
	TxUtil::add(time,day);
	TxUtil::add(time,hour);
	TxUtil::add(time,min);
	TxUtil::add(time,sec);
	TxUtil::add(time,milsec);

	src = time;
	time = { 0 };
	delete[] time;
}

void TxUtil::calculateHash(unsigned char* &hash, unsigned char * addr, unsigned char * val, unsigned char * nonce, unsigned char * cont, unsigned char * time)
{
	unsigned char * str = new unsigned char[32]{ 0 };
	//unsigned char * encrpytStr = new unsigned char[32]{ 0 };

	TxUtil::add(str, addr);
	TxUtil::add(str, val);
	TxUtil::add(str, nonce);
	TxUtil::add(str, cont);
	TxUtil::add(str, time);

	//SHA256_Encrpyt(str, 32, encrpytStr);

	hash = str;
	str = { 0 };

	delete[] str;
}

void TxUtil::add(unsigned char* &dest, unsigned char* src) {

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
		unsigned char * temp = new unsigned char[dest_cnt + src_cnt + 1];
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

		temp = { 0 };

		delete[] temp;
	}
}





























//unsigned char * TxUtil::addCharP(unsigned char* dest, bool data) {
//
//	const char* tf = data ? "1":"0";
//
//	size_t len_u = strlen((const char*)dest);
//	size_t len_b = sizeof(tf) / sizeof(char);
//
//	unsigned char* ret = new unsigned char[len_u + len_b];
//
//	for (int i = 0; i < sizeof(ret)/sizeof(char); i++) {
//		ret[i] = 0;
//	}
//
//	if (dest	 != NULL) {
//		//for (int i = 0; i < len_u+len_b; i++) {
//		//	ret[i] = dest[i];
//
//		//}
//
//		ret = dest;
//
//		strncat_s((char*)ret, len_u+len_b,tf, sizeof(data));
//	}
//	else {
//		ret = (unsigned char*)tf;
//	}
//	return ret;
//}
//
//unsigned char * TxUtil::addCharP(unsigned char* dest, unsigned char* data) {
//
//	size_t len_dest = strlen((const char*)dest);
//	size_t len_data = strlen((const char*)data);
//
//	unsigned char * ret = new unsigned char[len_dest + len_data];
//
//	for (int i = 0; i < sizeof(ret) / sizeof(char); i++) {
//		ret[i] = 0;
//	}
//
//	if (dest != NULL) {
//		ret = dest;
//
//		strncat_s((char*)ret, len_dest + len_data, (char*)data, sizeof(data));
//	}
//	else {
//		ret = data;
//	}
//
//
//	return ret;
//}
//
//unsigned char * TxUtil::addCharP(unsigned char* dest, unsigned int data) {
//
//
//	return 0;
//}