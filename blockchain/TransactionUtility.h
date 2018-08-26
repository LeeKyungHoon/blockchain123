#include<iostream>
#include<Windows.h>
#include<cstring>
#include"sha.h"
#include"filters.h"
#include"hex.h"
#include"base64.h"
#include<sstream>
#include<string>

using namespace CryptoPP;

namespace TransactionUtility {

	class TxUtil {
	public:
		void getTime(unsigned char* &);
		void calculateHash(unsigned char * &, unsigned char*, unsigned char*, unsigned char*, unsigned char*, unsigned char*);
		void calculateHash(unsigned char * &, unsigned char*, unsigned char*, unsigned char*, unsigned int, unsigned int);
		void calculateHash(unsigned char * &);
		void add(unsigned char* &, unsigned char*);
		int charCount(unsigned char* str);
	};
}