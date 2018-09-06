#include<WS2tcpip.h>
#include<ws2def.h>

#include"blockchain.h"
#include"wallet.h"

#include<thread>

#include <windows.h>
#include <wininet.h>
#include<string>
#include<iostream>
#include <sstream>
#include<fstream>

#include"boost/serialization/vector.hpp"
#include"boost/archive/text_oarchive.hpp"
#include"boost/archive/text_iarchive.hpp"

#pragma comment(lib, "Ws2_32.lib")

#define BUFF_SIZE 4096

void __chain_main(Blockchain *blockchain) {



}


void __server(void) {

	int client_size;

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	char buff_rcv[BUFF_SIZE];
	char buff_snd[BUFF_SIZE];

	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2, 2);

	WSAStartup(wVersionRequested, &wsaData);

	SOCKET sock = socket(PF_INET, SOCK_DGRAM, 0);

	if (sock == -1) {
		std::cout << "failed create socket" << std::endl;
		exit(1);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5000);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		std::cout << "failed binding" << std::endl;
		exit(1);
	}
	while (1) {
		client_size = sizeof(client_addr);

		recvfrom(sock, buff_rcv, BUFF_SIZE, 0, (struct sockaddr*)&client_addr, &client_size);
		switch (buff_rcv[0])
		{
		case 5:
			//transaction
			//chain.occurTransaction();
			break;
		case 6:
			//block
			//chain.rcv_block();
			break;
		default:
			break;
		}
	}

}


void __mining(Blockchain *chain) {
	while (running_flag) {
		chain->makeNewBlock();
		chain->mineBlock();
		Block *b = chain->getChain().at(0);
		std::cout << b->blockHash << std::endl;
		std::ofstream fout("./test123.txt", std::ios_base::out | std::ios_base::binary);
		fout.write((char*)b, sizeof(b));
		fout.close();
		//Block *b1;
		//std::ifstream fin("./test123.txt", std::ios_base::in | std::ios_base::binary);
		//fin.read((char*)&b1, sizeof(&b1));
		//fin.close();
		//std::cout << b1->blockHash << std::endl;


		//client(chain->getChain().back());
	}
}


int main(void) {

	//Blockchain *chain = Blockchain::GetInstance();

	//__mining(chain);

	//std::thread*p2Thread = new std::thread(__mining, chain);
	//std::thread *server = new std::thread(__server);
	//std::thread *serv_client = new std::thread(serv_client);
	//p2Thread->join();
	//server->join();
	//serv_client->join();

	Block *b;
	std::ifstream fin("./test123.txt", std::ios_base::in | std::ios_base::binary);
	fin.read((char*)&b, sizeof(&b));
	fin.close();
	std::cout << b->blockHash << std::endl;

	system("pause");
	return 0;
}




































void __wallet_main(Wallet* wallet, Blockchain* blockchain) {
	//1 generateKey;
	//2 saveKey;
	//3 loadKey;
	//4 makeTransaction -> sign -> broadcast;
	//4-1 sign inner key;
	//4-2 sign load key;
	//5 show privKey;
	//6 show pubKey;
	//7 broadcast
	//8 exit;
	unsigned int cmd = 0;
	std::string tStr;


	std::string toAddr = "";
	std::string toVal = "";
	std::string fee = "";

	printf("1. generate Key\n2. save private Key\n3. load Key\n4. make new Transaction\n5. show Private Key\n6. show public Key\n7. exit\n");

	while (running_flag) {
		scanf_s("%d", &cmd);

		switch (cmd)
		{
		case 1:
			wallet->geneKey();
			break;
		case 2:
			wallet->save();
			printf("success save the private Key\n");
			break;
		case 3:
			printf("is not working\n");
			break;
			wallet->load();
			break;
		case 4:
			printf("who spend money? :");
			scanf_s("%s", &toAddr);
			printf("how much spend? : ");
			scanf_s("%s", &toVal);
			printf("how much decide fee? : ");
			scanf_s("%s", &fee);
			wallet->makeRawTransaction(toAddr.c_str(), toVal.c_str(), fee.c_str());

			printf("1. signed wallet key or 2. load key? : ");
			scanf_s("%d", &cmd);
			if (cmd == 1) {
				TransactionBase tx = *wallet->list->getLastElem();
				wallet->signTransaction(tx, wallet->keyPairsAndBalance.front().privKey);
				printf("signature is ");
				for (int i = 0; i < 42; i++) {
					printf("%hhx", tx.txSignedMsg[i]);
				}
				printf("\n");
				blockchain->occurTransaction(&tx);
			}
			else if (cmd == 2) {
				printf("is not working now\n");
			}
			else {
				printf("wrong command\n");
			}

			break;
		case 5:
			if (!wallet->keyPairsAndBalance.empty()) {
				wallet->privatekeyHexEncoding(tStr, wallet->keyPairsAndBalance.front().privKey);
				printf("%s\n", tStr.c_str());
				tStr.clear();
			}
			else {
				printf("키를 생성해야 합니다.\n");
			}
			break; \
		case 6:
			if (!wallet->keyPairsAndBalance.empty()) {
				wallet->publickeyHexEncoding(tStr, wallet->keyPairsAndBalance.front().pubKey);
				printf("%s\n", tStr.c_str());
				tStr.clear();
			}
			else {
				printf("키를 생성해야 합니다.\n");
			}
			break;
		case 7:
			//broadcast
			break;
		case 8:
			running_flag = !running_flag;
			break;
		default:
			printf("다시 입력해주세요\n");
			printf("1. generate Key\n2. save private Key\n3. load Key\4. make new Transaction\n5. show Private Key\n6. show public Key\n7. exit\n");
			break;
		}


	}

}