#include<WS2tcpip.h>
#include<ws2def.h>

#include"blockchain.h"
#include"node.h"

#include<thread>

#include <windows.h>
#include <wininet.h>
#include<string>
#include<iostream>
#include <sstream>
#include<fstream>

#pragma comment(lib, "Ws2_32.lib")

#define BUFF_SIZE 4096

std::vector<sock_serialize> peers;
client c;
sock_serialize _my_peer;

void __mining(Blockchain *chain) {
	while (running_flag) {
		chain->makeNewBlock();
		chain->mineBlock();
		c.to_peer(*chain->getChain().end()[-1], peers);
	}
}


int main(void) {

	Blockchain *chain = Blockchain::GetInstance();
	
	peers = c.to_server().getAddrList();
	_my_peer = peers.end()[-1];
	peers.pop_back();
	if (peers.size() > 0) {
		c.to_peer(peers);

		std::cout << "block list" << std::endl;
		for (auto it : chain->getChain()) {
			std::cout << "blockhash is " << it->blockHash << std::endl;
		}
	};

	for (auto it : peers) {
		std::cout << it.getAddr() << " " << it.getPort() << std::endl;
	}

	server s(_my_peer);

	std::thread*p2Thread = new std::thread(__mining, chain);
	std::thread *t = new std::thread(&server::s_server, &s);
	p2Thread->join();
	t->join();

	system("pause");
	return 0;
}