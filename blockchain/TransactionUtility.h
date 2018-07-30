#pragma once
#include<Windows.h>

namespace TransactionUtility{

	class TxUtil {
	public :
		void getTime(unsigned char* &);
		void calculateHash(unsigned char * &,unsigned char*,unsigned char*, unsigned char*, unsigned char*, unsigned char*);
		void add(unsigned char* &, unsigned char* );
	};

}