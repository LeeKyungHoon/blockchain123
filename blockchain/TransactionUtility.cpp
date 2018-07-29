#pragma once


#include"TransactionUtility.h"

using namespace TransactionUtility;
using namespace std::chrono;

unsigned char* TxUtil::getTime() {



	return 0;
}

unsigned char* TransactionUtility::TxUtil::calculateHash(unsigned char * addr, unsigned char * val, unsigned char * nonce, unsigned char * cont, unsigned char * time)
{
	unsigned char * str = new unsigned char[32]{ 0 };
	//unsigned char * encrpytStr = new unsigned char[32]{ 0 };

	TxUtil::add(str, addr);
	TxUtil::add(str, val);
	TxUtil::add(str, nonce);
	TxUtil::add(str, cont);
	TxUtil::add(str, time);

	//SHA256_Encrpyt(str, 32, encrpytStr);

	return str;
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
		unsigned char * temp = new unsigned char[dest_cnt + src_cnt + 1];
		for (int j = 0; j < dest_cnt; j++) {
			temp[j] = dest[j];
		}

		i = 0;
		for (int i = 0; i < dest_cnt + src_cnt + 1; i++)
		{
			if (src[i] == '\0') { temp[dest_cnt+i] = '\0'; break; }
			else {
				temp[dest_cnt + i] = src[i];
			}
		}

		dest = temp;
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