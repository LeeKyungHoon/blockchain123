
#include"block.h"

class Blockchain {
private:
	Block * firstBlock;
	Block * curBlockNode;
public:
	Blockchain();
	void geneBlock();
	void makeNewBlock();
	void mineBlock();
	void occurTransaction();
	void printBC();

};