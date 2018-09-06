#include<WS2tcpip.h>
#include<ws2def.h>

#include<Windows.h>
#include<WinInet.h>
#include<string>
#include<iostream>
#include<sstream>

#include"serialization.h"

#pragma comment(lib, "Ws2_32.lib")

#define BUFF_SIZE 4096

class client {
private:

	int serv_addr_size;
	struct sockaddr_in serv_addr;
	char buff_rcv[BUFF_SIZE];

	const std::string loopback = "127.0.0.1";

public:
	client();
	~client();
	void start();
	void clean();
	sock_vector_serialize to_server();
	void to_peer(const Block &block, const std::vector<sock_serialize> & peers);
	void to_pper(const TransactionBase &Tx, const std::vector<sock_serialize> & peers);

};