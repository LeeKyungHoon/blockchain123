#pragma once

#include"TransactionUtility.h"
#include<string>

using namespace TransactionUtility;

unsigned char * TxUtil::addCharP(unsigned char* dest, bool data) {

	unsigned char tf = data ? '1' : '0';

	size_t len_u = strlen((const char*)dest);
	size_t len_b = sizeof(tf) / sizeof(char);

	printf("%d, %d\n", len_u, len_b);

	unsigned char* ret = new unsigned char[len_u + len_b];


	for (int i = 0; i < strlen((const char*)ret); i++) {
		printf("%c", ret[i]);
	}

	printf("\n");

	for (int i = 0; i < len_u+len_b; i++) {
		ret[i] = 0;
	}


	//for (int i = 0; i < sizeof(ret)/sizeof(char); i++) {
	//	ret[i] = 0;
	//}

	for (int i = 0; i < strlen((const char*)ret); i++) {
		printf("%c", ret[i]);
	}
	printf("\n");

	printf("res : %s, ret length : %d, ret size : %d\n",ret, strlen((const char*)ret), sizeof(ret));
	printf("dest : %s, dest length : %d, dest size : %d\n", dest, strlen((const char*)dest), sizeof(dest));

	if (data != NULL) {
		for (int i = 0; i < len_u; i++) {
			ret[i] = dest[i];

		}
		ret[len_u] = (unsigned char)tf;
	}
	else {
		printf("ret : %s, ret length : %d, ret size : %d\n", ret, strlen((const char*)ret), sizeof(ret));
		
		//for (int i = 0; i < sizeof(ret) / sizeof(char); i++) {
			//ret[i] = tf;
		//}
		ret[0] = tf;

	}
	printf("ret : %s, ret length : %d, ret size : %d\n", ret, strlen((const char*)ret), sizeof(ret));

	return ret;
}

unsigned char * TxUtil::addCharP(unsigned char* dest, unsigned char* data) {


	return 0;
}

unsigned char * TxUtil::addCharP(unsigned char* dest, unsigned int data) {


	return 0;
}