#pragma once

#include"KISA_SHA256.h"
#include<string>
#include<chrono>
#include<ctime>

namespace TransactionUtility{

	class TxUtil {
	public :
		unsigned char* getTime();
		unsigned char* getHash();
		unsigned char* combElem();
	};

}