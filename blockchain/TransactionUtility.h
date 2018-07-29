#pragma once

#include"KISA_SHA256.h"
#include<string.h>
#include<chrono>
#include<ctime>

namespace TransactionUtility{

	class TxUtil {
	public :
		unsigned char* getTime();
		unsigned char* calculateHash(unsigned char*,unsigned char*, unsigned char*, unsigned char*, unsigned char*);
		void add(unsigned char* &, unsigned char* );
	};

}