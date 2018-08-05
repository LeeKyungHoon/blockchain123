
//#include"Node.h"
#include"transactionList.h"
#include<vector>

namespace merkle {
	class merkleTree {
		std::vector<unsigned char*> __iterator;

	public:
		void getRoot(unsigned char* &root, const TransactionList& list);
	};

}