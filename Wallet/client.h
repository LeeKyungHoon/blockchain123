#pragma once

#include<WS2tcpip.h>
#include<ws2def.h>

#include "serialization.h"

#pragma comment(lib, "Ws2_32.lib")

#define BUFF_SIZE 4096

class Client {
private:

	int serv_addr_size;
	struct sockaddr_in serv_addr;
	char buff_rcv[BUFF_SIZE] = { 0 };

	const string loopback = "127.0.0.1";


public:
	Client() {
	
		WORD wVersionReauest;
		WSADATA wsaData;

		wVersionReauest = MAKEWORD(2, 2);
		WSAStartup(wVersionReauest, &wsaData);
	
	};
	~Client() {
	
		WSACleanup();

	};

	sock_vector_serialize to_server() {

		SOCKET s = socket(PF_INET, SOCK_DGRAM, 0);

		if (-1 == s) {
			cout << "failed create socket" << endl;
			exit(1);
		}
		memset(&buff_rcv, 0, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(5000);
		inet_pton(AF_INET, loopback.c_str(), &serv_addr.sin_addr.s_addr);

		sendto(s, "", BUFF_SIZE, 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

		serv_addr_size = sizeof(serv_addr);

		recvfrom(s, buff_rcv, BUFF_SIZE, 0, (struct sockaddr*)&serv_addr, &serv_addr_size);

		stringstream ss(buff_rcv);
		boost::archive::text_iarchive ar(ss);
		sock_vector_serialize serial;
		ar >> serial;

		closesocket(s);

		return serial;
	
	}

	void to_peer(const TransactionBase& tx, const vector<sock_serialize> & peers) {

		TxSerialize ts(tx);
		stringstream ss;
		boost::archive::text_oarchive ar(ss);
		ar & ts;

		string _send_ = "1";
		_send_.append(ss.str());

		for (auto a : peers) {

			SOCKET s = socket(PF_INET, SOCK_DGRAM, 0);

			if (-1 == s) {
				cout << "failed create socket" << endl;
				exit(1);
			}

			memset(&serv_addr, 0, sizeof(serv_addr));
			serv_addr.sin_family = AF_INET;
			serv_addr.sin_port = htons(a.getPort());
			inet_pton(AF_INET, a.getAddr().c_str(), &serv_addr.sin_addr.s_addr);

			sendto(s, _send_.c_str(), _send_.length() + 1, 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

				
			closesocket(s);
		}

	}
	
};