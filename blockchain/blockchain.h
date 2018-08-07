
#include"block.h"

class Blockchain {
private:
	std::vector<Block*> chain;
public:
	Blockchain();
	void geneBlock();
	void makeNewBlock();
	void mineBlock();
	void occurTransaction(std::string, std::string, std::string, std::string);

};