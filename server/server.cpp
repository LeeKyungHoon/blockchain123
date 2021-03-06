
#include <iostream>
#include <WS2tcpip.h>
#include <ws2def.h>
#include <vector>
#include <stdio.h>
#include <sstream>
#include<fstream>

#include"boost/serialization/vector.hpp"
#include"boost/archive/text_oarchive.hpp"
#include"boost/archive/text_iarchive.hpp"

#pragma comment(lib, "Ws2_32.lib")

#define BUFFER_SIZE 4096

class sock_addr {
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & address;
		ar & port;
	}
	std::string address;
	USHORT port;
public:
	sock_addr() {}
	sock_addr(std::string a, USHORT p) :address(a), port(p) {}
	std::string getAddr() { return address; }
	USHORT getPort() { return port; }
	virtual ~sock_addr() {}
};

class Boost {
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar& addr_list;
	}
	std::vector<sock_addr> addr_list;
public:
	Boost() {};
	void AddAddr_list(const sock_addr& sock) { addr_list.push_back(sock_addr(sock)); };
	void Print() {
		for (std::vector<sock_addr>::iterator it = addr_list.begin(); it != addr_list.end(); ++it) {
			std::cout << it->getAddr() << std::endl;
			std::cout << it->getPort() << std::endl;
		}

	}
};

int main()
{
	Boost boost;

	int client_size;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	char buff_rcv[BUFFER_SIZE]{ 0 };
	char buff_snd[BUFFER_SIZE]{ 0 };
	char addr_ip[256];

	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2, 2);

	WSAStartup(wVersionRequested, &wsaData);


	client_size = sizeof(client_addr);

	SOCKET sock = socket(PF_INET, SOCK_DGRAM, 0);


	if (sock == -1) {
		std::cout << "failed create socket" << std::endl;
		exit(1);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5000);
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	if (bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		std::cout << "failed binding" << std::endl;
		exit(1);
	}

	while (true) {
		recvfrom(sock, buff_rcv, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &client_size);
		printf("receive addr : %s\n", buff_rcv);
		inet_ntop(AF_INET, &client_addr.sin_addr.S_un.S_addr, addr_ip, sizeof(addr_ip));
		
		std::cout << addr_ip << std::endl;
		std::cout << ntohs(client_addr.sin_port) << std::endl;
		boost.AddAddr_list(sock_addr(addr_ip, ntohs(client_addr.sin_port)));
		{
			std::stringstream ofs;
			boost::archive::text_oarchive ar(ofs);
			ar & boost;
			sendto(sock, ofs.str().c_str(), strlen(ofs.str().c_str()) + 1, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
		}
	}


}
