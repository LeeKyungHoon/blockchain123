#include<WS2tcpip.h>
#include<ws2def.h>

#include<Windows.h>
#include<WinInet.h>
#include<string>
#include<iostream>
#include<sstream>

#include<thread>

#include"serialization.h"
#include"blockchain.h"
#include"client.h"


#pragma comment(lib, "Ws2_32.lib")

#define BUFF_SIZE 4096

class server {
private:
	int c_a_s;
	struct sockaddr_in c_a;
	struct sockaddr_in s_a;
	char buff_rcv[BUFF_SIZE];
	char buff_snd[BUFF_SIZE]{ 0 };

	const std::string loopback = "127.0.0.1";

public:
	server() {};
	server(sock_serialize s) {
		memset(&s_a, 0, sizeof(s_a));
		s_a.sin_family = AF_INET;
		s_a.sin_port = htons(s.getPort());
		inet_pton(AF_INET, s.getAddr().c_str(), &s_a.sin_addr.s_addr);
		//s_a.sin_addr.S_un.S_addr = htonl(s.getAddr());
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

		
		if (bind(sock, (struct sockaddr*)&s_a, sizeof(s_a)) == -1) {
			std::cout << "failed binding" << std::endl;
			exit(1);
		}

		while (true) {
			std::cout << "running" << std::endl;
			c_a_s = sizeof(c_a);
			recvfrom(sock, buff_rcv, BUFF_SIZE, 0, (struct sockaddr*)&c_a, &c_a_s);


			//blocks send
			if (memcmp(buff_rcv, "0", 1) == 0) {
				std::cout << "blocks send to client " << std::endl;
				Blockchain *chain = Blockchain::GetInstance();
				for (Block* b : chain->getChain()) {
					std::cout <<"current send block hash is : "<< b->blockHash << std::endl;
					if (memcmp(b->blockHash, "00000", 5) != 0)continue;
					BlockSerialize bs(*b);
					std::stringstream ss;
					boost::archive::text_oarchive ar(ss);
					ar & bs;
					std::cout << "curren serialized block string is : " << ss.str() << std::endl;
					std::cout << "socket size is : " << sizeof(ss.str().c_str())+1 << std::endl;
					sendto(sock, ss.str().c_str(), strlen(ss.str().c_str()) + 1, 0, (struct sockaddr*)&c_a, c_a_s);
				}
				sendto(sock, "1", 2, 0, (struct sockaddr*)&c_a, c_a_s);
			}
			//tx recive
			else if (memcmp(buff_rcv, "1", 1) == 0) {

			}
			//block recive
			else {
				std::cout << "recived blocks are " << buff_rcv << std::endl;

				std::stringstream ss(buff_rcv);
				boost::archive::text_iarchive ar(ss);
				BlockSerialize bs;
				ar >> bs;
				Blockchain * chain = Blockchain::GetInstance();
				chain->rcv_block(bs.getBlock());
			}

			memset(&buff_rcv, 0, sizeof(BUFF_SIZE));
		}
		WSACleanup();
	};
};