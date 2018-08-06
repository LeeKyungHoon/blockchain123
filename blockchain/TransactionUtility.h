#pragma once
#include<iostream>
#include<Windows.h>
#include<cstring>
#include"cryptopp700/sha.h"
#include"cryptopp700/filters.h"
#include"cryptopp700/hex.h"

using namespace CryptoPP;

namespace TransactionUtility {

	class TxUtil {
	public:
		void getTime(unsigned char* &);
		void calculateHash(unsigned char * &, unsigned char*, unsigned char*, unsigned char*, unsigned char*, unsigned char*);
		void calculateHash(unsigned char * &, unsigned char*, unsigned char*, unsigned char*, unsigned int, unsigned int);
		void calculateHash(unsigned char * &);
		void add(unsigned char* &, unsigned char*);
		void add(unsigned char* &, unsigned int);
		void replace(unsigned char* &, unsigned char*);
	};

}