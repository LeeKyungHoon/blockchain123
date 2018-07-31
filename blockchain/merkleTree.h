
namespace merkle {
	class merkleTree {
	private:
		unsigned char* merkleRoot;
		unsigned int levels = 0;

	public:
		merkleTree();
		unsigned char* getRoot() { return merkleRoot; };

	};

}