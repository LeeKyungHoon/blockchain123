#include"transactionBase.h"
#include"block.h"

#include"boost/serialization/vector.hpp"
#include"boost/archive/text_iarchive.hpp"
#include"boost/archive/text_oarchive.hpp"

#include<Windows.h>

class sock_serialize {
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & address;
		ar & port;
	}
	std::string address;
	USHORT port;
public:
	sock_serialize() {}
	sock_serialize(std::string a, USHORT p) :address(a), port(p) {}
	std::string getAddr() { return address; }
	USHORT getPort() { return port; }
	virtual ~sock_serialize() {}
};

class sock_vector_serialize {
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar& addr_list;
	}
	std::vector<sock_serialize> addr_list;
public:
	sock_vector_serialize() {};
	void AddAddr_list(const sock_serialize& sock) { addr_list.push_back(sock_serialize(sock)); };
	void Print() {
		for (std::vector<sock_serialize>::iterator it = addr_list.begin(); it != addr_list.end(); ++it) {
			std::cout << it->getAddr() << std::endl;
			std::cout << it->getPort() << std::endl;
		}
	}
	std::vector<sock_serialize> getAddrList() {
		return addr_list;
	}
};

class tx_serialize {
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & Tx;
	}
	TransactionBase Tx;
public:
	tx_serialize() {};
	tx_serialize(TransactionBase Tx) :Tx(Tx) {};
	virtual ~tx_serialize() {};
};

class block_serialize {
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & block;
	}
	Block block;
public:
	block_serialize() {};
	block_serialize(Block block) :block(block) {};
	virtual ~block_serialize() {};
};