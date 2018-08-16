//#pragma comment(lib, "../../../cryptopp700/Win32/Output/Release/cryptlib.lib")
#pragma once
#include<iostream>
#include<Windows.h>
#include<cstring>
//#include<sha.h>
//#include<filters.h>
//#include<hex.h>
#include"sha.h"
#include"filters.h"
#include"hex.h"

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