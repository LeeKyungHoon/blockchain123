#pragma once


#include<WS2tcpip.h>
#include<ws2def.h>

#include"serialization.h"
#include"block.h"

#pragma comment(lib, "Ws2_32.lib")

#define BUFF_SIZE 4096


class server {

private:
	int c_a_s;
	struct sockaddr_in c_a;
	struct sockaddr_in s_a;
	char buff_rcv[BUFF_SIZE];
	char buff_snd[BUFF_SIZE]{ 0 };

	const string loopback = "127.0.0.1";

public :
	server() {};
	server(sock_serialize s) {
		memset(&s_a, 0, sizeof(s_a));
		s_a.sin_family = AF_INET;
		s_a.sin_port = htons(s.getPort());
		inet_pton(AF_INET, s.getAddr().c_str(), &s_a.sin_addr.s_addr);
	};
	~server() {};

	void s_server() {
		WORD wVersionRequest;
		WSADATA wsaData;

		wVersionRequest = MAKEWORD(2, 2);
		WSAStartup(wVersionRequest, &wsaData);


		SOCKET sock = socket(PF_INET, SOCK_DGRAM, 0);

		if (sock == -1) {
			std::cout << "failed create socket" << std::endl;
			exit(1);
		}

		if (::bind(sock, (struct sockaddr*)&s_a, sizeof(s_a))==-1) {
			cout << "failed binding" << endl;
			exit(1);
		}

		while (true) {
			std::cout << "running" << std::endl;
			c_a_s = sizeof(c_a);
			recvfrom(sock, buff_rcv, BUFF_SIZE, 0, (struct sockaddr*)&c_a, &c_a_s);


			//block recive
			std::cout << "recived blocks are " << buff_rcv << std::endl;

			std::stringstream ss(buff_rcv);
			boost::archive::text_iarchive ar(ss);
			BlockSerialize bs;
			ar >> bs;
			bs.getTxList();

			// balance calculation
			{
				TransactionList *txList = TransactionList::GetInstance();
				Wallet * w = Wallet::GetInstance();



			}

			memset(&buff_rcv, 0, sizeof(BUFF_SIZE));
		}
		WSACleanup();
	};



};


