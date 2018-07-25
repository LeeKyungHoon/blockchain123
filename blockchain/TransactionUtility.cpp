#pragma once

#include"TransactionUtility.h"
#include<string>

using namespace TransactionUtility;

unsigned char * TxUtil::addCharP(unsigned char* dest, bool data) {

	const char* tf = data ? "1":"0";

	size_t len_u = strlen((const char*)dest);
	size_t len_b = sizeof(tf) / sizeof(char);

	unsigned char* ret = new unsigned char[len_u + len_b];

	for (int i = 0; i < sizeof(ret)/sizeof(char); i++) {
		ret[i] = 0;
	}

	if (data != NULL) {
		for (int i = 0; i < len_u; i++) {
			ret[i] = dest[i];

		}
		ret[len_u] = (unsigned char)tf;
	}
	else {
		ret = (unsigned char*)tf;
	}
	return ret;
}

unsigned char * TxUtil::addCharP(unsigned char* dest, unsigned char* data) {

	size_t len_dest = strlen((const char*)dest);
	size_t len_data = strlen((const char*)data);

	unsigned char * ret = new unsigned char[len_dest + len_data];

	for (int i = 0; i < sizeof(ret) / sizeof(char); i++) {
		ret[i] = 0;
	}

	if (data != NULL) {

	}
	else {

	}


	return 0;
}

unsigned char * TxUtil::addCharP(unsigned char* dest, unsigned int data) {


	return 0;
}