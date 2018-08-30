
#include <iostream>
#include <WS2tcpip.h>
#include <ws2def.h>
#include <vector>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

#define BUFFER_SIZE 4096

int main()
{
	std::vector<sockaddr_in> addr_list;

	int client_size;

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	char buff_rcv[BUFFER_SIZE];
	char buff_snd[BUFFER_SIZE];

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

		sprintf_s(buff_snd, "%s%s", buff_rcv, buff_snd);

		sendto(sock, buff_snd, strlen(buff_snd) + 1, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
	}


}
