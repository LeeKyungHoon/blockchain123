
#include <iostream>
#include <WS2tcpip.h>
#include <ws2def.h>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

#define BUFFER_SIZE 4096

int main()
{
	std::vector<sockaddr_in> addr_list;

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	char buff_rcv[BUFFER_SIZE];
	char buff_snd[BUFFER_SIZE];

	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2, 2);

	WSAStartup(wVersionRequested, &wsaData);

	if (socket(AF_INET, SOCK_DGRAM, 0) == -1) {
		std::cout << "failed create socket" << std::endl;
		exit(1);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(50000);
	server.


}
