#include"transactionList.h"
#include"block.h"

#include<sstream>
#include<iostream>

#include"boost/serialization/vector.hpp"
#include"boost/archive/text_iarchive.hpp"
#include"boost/archive/text_oarchive.hpp"
#include"boost/serialization/unordered_map.hpp"
#include"boost/serialization/string.hpp"

#include<Windows.h>

#pragma once

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

class TxSerialize {
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar& hash;
		ar& addr;
		ar& val;
		ar& fee;
		ar& msg;
		ar& time;
		ar& sign;
	}
	std::string hash;
	std::string addr;
	std::string val;
	std::string fee;
	std::string msg;
	std::string time;
	std::string sign;
public:
	TxSerialize() {};
	TxSerialize(const TransactionBase & t) {
		hash = (const char*)t.txHash;
		addr = (const char*)t.txToAddr;
		val = (const char*)t.txVal;
		fee = (const char*)t.txFee;
		msg = (const char*)t.txSignedMsg;
		time = (const char*)t.txTime;
		sign = t.txSign;
	};
	TransactionBase getTransaction() {
		return TransactionBase(hash.c_str(), addr.c_str(), val.c_str(), fee.c_str(), msg.c_str(), time.c_str(), sign.c_str());
	};
	virtual ~TxSerialize() {};
};

class TxListSerialize {
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & transactionHashMap;
	}
	std::unordered_map<std::string, TxSerialize> transactionHashMap;
public:
	TxListSerialize() {};
	TxListSerialize(TransactionList* list) {
		for (auto it : list->getList()) {
			transactionHashMap.insert(std::pair<std::string, TxSerialize>((const char*)it.first, TxSerialize(it.second)));
		}
	};
	void getTransactionList() {
		std::unordered_map<PUCHAR, TransactionBase> list;

		for (auto it : transactionHashMap) {
			list.insert(std::pair<unsigned char*, TransactionBase>((unsigned char*)it.first.c_str(), it.second.getTransaction()));
		}

		TransactionList *txList = TransactionList::GetInstance();
		txList->add(list);
	};
	virtual ~TxListSerialize() {};

};

class HeaderSerialize {
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar& prev;
		ar& root;
		ar& time;
		ar& diff;
		ar& nonce;
	}
	std::string prev;
	std::string root;
	std::string time;
	std::string diff;
	std::string nonce;

public:
	HeaderSerialize() {};
	HeaderSerialize(const Blockheader & h) {
		prev = (const char*)h.hashPrevBlock;
		root = (const char*)h.hashMerkleRoot;
		time = (const char*)h.Time;
		diff = std::to_string(h.Difficulty);
		nonce = std::to_string(h.Nonce);
	};
	Blockheader getBlockheader() {
		//std::cout << "hashPrevBlock : " << prev << " merkleroot : " << root << " time : " << time << " diff : " << diff << " nonce : " << nonce << std::endl;
		return Blockheader((unsigned char*)prev.c_str(), (unsigned char*)root.c_str(), (unsigned char*)time.c_str(), (unsigned int)std::atoi(diff.c_str()), (unsigned int)std::atoi(nonce.c_str()));
	};
	virtual ~HeaderSerialize() {};
};


class BlockSerialize {
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar& hash;
		ar& hs;
		ar& tls;
	}
	std::string hash;
	HeaderSerialize hs;
	TxListSerialize tls;
public:
	BlockSerialize() {};
	BlockSerialize(const Block& b) {
		hash = (const char*)b.blockHash;
		hs = HeaderSerialize(*b.header);
		tls = TxListSerialize(b.List);
	};
	Block getBlock() {
		//std::cout << "hash is : " << hash << std::endl;
		tls.getTransactionList();
		return Block((PUCHAR)hash.c_str(), hs.getBlockheader());
	};
	void getTxList() {
		tls.getTransactionList();
	};
	virtual ~BlockSerialize() {};
};
