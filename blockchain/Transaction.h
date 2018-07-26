
#include"transactionBase.h"


class Transaction :public TransactionBase {

public :
	Transaction();
	Transaction(TransactionBase&);
	void setTransaction();
	Transaction getTransaction();
};