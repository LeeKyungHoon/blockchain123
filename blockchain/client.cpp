#include "client.h"

void client::start()
{
	WORD wVersionRequest;
	WSADATA wsaData;

	wVersionRequest = MAKEWORD(2, 2);
	WSAStartup(wVersionRequest, &wsaData);
}

void client::clean()
{
	WSACleanup();
}

sock_vector_serialize client::to_server()
{
	SOCKET sock = socket(PF_INET, SOCK_DGRAM, 0);

	if (-1 == sock) {
		std::cout << "failed create socket" << std::endl;
		exit(1);
	}
	memset(&buff_rcv, 0, sizeof(BUFF_SIZE));

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5000);
	inet_pton(AF_INET, loopback.c_str(), &serv_addr.sin_addr.s_addr);

	sendto(sock, "", BUFF_SIZE, 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	serv_addr_size = sizeof(serv_addr);

	recvfrom(sock, buff_rcv, BUFF_SIZE, 0, (struct sockaddr*)&serv_addr, &serv_addr_size);

	std::stringstream ss(buff_rcv);
	boost::archive::text_iarchive ar(ss);
	sock_vector_serialize serial;
	ar >> serial;

	closesocket(sock);

	return serial;
}

void client::to_peer(const Block &b, const std::vector<sock_serialize> & peers)
{
	std::vector<sock_serialize> _peers = peers;
	BlockSerialize bs(b);
	std::stringstream ss;
	boost::archive::text_oarchive ar(ss);
	ar & bs;

	for (std::vector<sock_serialize>::iterator peer = _peers.begin(); peer != _peers.end(); ++peer) {
		SOCKET sock = socket(PF_INET, SOCK_DGRAM, 0);

		if (-1 == sock) {
			std::cout << "failed create socket" << std::endl;
			exit(1);
		}
		memset(&buff_rcv, 0, sizeof(BUFF_SIZE));

		memset(&serv_addr, 0, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(peer->getPort());
		inet_pton(AF_INET, peer->getAddr().c_str(), &serv_addr.sin_addr.s_addr);

		sendto(sock, ss.str().c_str(), strlen(ss.str().c_str()) + 1, 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

		closesocket(sock);
	}
}

void client::to_peer(const std::vector<sock_serialize>& peers)
{
	Blockchain *chain = Blockchain::GetInstance();
	chain->rmvAll();
	std::vector<sock_serialize> _peers = peers;
	int cnt = 1;

	for (std::vector<sock_serialize>::iterator peer = _peers.begin(); peer != _peers.end()-1; ++peer) {
		SOCKET sock = socket(PF_INET, SOCK_DGRAM, 0);

		if (-1 == sock) {
			std::cout << "failed create socket" << std::endl;
			exit(1);
		}
		memset(&buff_rcv, 0, sizeof(BUFF_SIZE));

		memset(&serv_addr, 0, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(peer->getPort());
		inet_pton(AF_INET, peer->getAddr().c_str(), &serv_addr.sin_addr.s_addr);
		std::cout << "send to " << peer->getAddr() << " : " << peer->getPort() << std::endl;
		sendto(sock, "0", 2, 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

		while (1)//1 is end of string vector 
		{
			serv_addr_size = sizeof(serv_addr);
			recvfrom(sock, buff_rcv, BUFF_SIZE, 0, (struct sockaddr*)&serv_addr, &serv_addr_size);
			if (std::memcmp(buff_rcv, "1", 1) == 0)break;
			std::cout << "recived blocks are " << buff_rcv << std::endl;

			std::stringstream ss(buff_rcv);
			boost::archive::text_iarchive ar(ss);
			BlockSerialize bs;
			ar >> bs;
			chain->rcv_block(bs.getBlock());
			memset(&buff_rcv, 0, sizeof(BUFF_SIZE));
		}

		closesocket(sock);
	}
}
