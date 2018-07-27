#pragma once

#include"TransactionUtility.h"

using namespace TransactionUtility;
using namespace std::chrono;


unsigned char * TxUtil::combElem(const TransactionBase& txBase) {




}

unsigned char * TxUtil::getHash(const TransactionBase& txBase) {
	unsigned char* combinedElem = combElem(txBase);



}

unsigned char* TxUtil::getTime() {
	high_resolution_clock::time_point p = high_resolution_clock::now();

	milliseconds ms = duration_cast<milliseconds>(p.time_since_epoch());

	seconds s = duration_cast<seconds>(ms);
	std::time_t t = s.count();
	std::size_t fractional_seconds = ms.count() % 1000;
	//std::cout << std::ctime(&t) << std::endl;
	//std::cout << fractional_seconds << std::endl;

	return 0;
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