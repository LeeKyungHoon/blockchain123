#include "client.h"
#include "wallet.h"
#include "server.h"
#include "server.h"
#include <thread>

#define BUFFERSIZE 128

vector<sock_serialize> peers;
Client c;
Wallet* wallet = Wallet::GetInstance();

void _main_cmd() {
	cout << "1. generate Key" << endl;
	cout << "2. save private Key" << endl;
	cout << "3. load Key" << endl;
	cout << "4. make new Transaction" << endl;
	cout << "5. show private key" << endl;
	cout << "6. show public key" << endl;
	cout << "7. broadcasting" << endl;
	cout << "8. exit" << endl;
}

void _generate_key() {
	if (wallet->keys.size() == 0) {
		wallet->geneKey();

		cout << "current have keys" << endl;
		for (auto a : wallet->keys) {
			cout << "private key : " << wallet->privatekeyHexEncoding(a.privKey) << endl;
			cout << "public  key : " << wallet->publickeyHexEncoding(a.pubKey) << endl;
			cout << endl;
		}
	}
	else {
		cout << "you have only one key" << endl;
	}
}

void _save_key() {
	wallet->saveAll();
	printf("success save the private Key\n");
}

void _sign_transaction() {
	int cmd;

	printf("signed wallet key or load key? : ");
	cin >> cmd;

	if (cmd == 1) {
		TransactionBase tx(wallet->list->getLastValue());
		wallet->signTransaction(tx, wallet->keys[0].privKey);
		printf("signature is ");
		cout << tx.txSignedMsg << endl;
		printf("\n");
	}
	else if (cmd == 2) {
		printf("is not working now\n");
	}
	else {
		printf("wrong command\n");
	}
	c.to_peer(wallet->list->getLastValue(), peers);

	cin.clear();
	cin.ignore(256, '\n');

	//auto broadcast

}

void _show_private_key() {
	if (!wallet->keys.empty()) {
		cout << wallet->privatekeyHexEncoding(wallet->keys[0].privKey) << endl;
	}
	else
	{
		printf("키를 생성해야 합니다.\n");
	}
}

void _show_public_key() {
	if (!wallet->keys.empty()) {
		cout << wallet->publickeyHexEncoding(wallet->keys[0].pubKey) << endl;
	}
	else {
		printf("키를 생성해야 합니다.\n");
	}
}

void _make_raw_transaction() {

	cin.clear();
	cin.ignore(256, '\n');

	string str;

	char addr[BUFFERSIZE] = { 0 };
	char val[BUFFERSIZE] = { 0 };
	char fee[BUFFERSIZE] = { 0 };

	printf("who spend money? :");
	getline(cin, str);
	memcpy_s(addr, sizeof(addr), str.c_str(), str.length());
	cin.clear();

	printf("how much spend? : ");
	getline(cin, str);
	memcpy_s(val, sizeof(val), str.c_str(), str.length());
	cin.clear();

	printf("how much decide fee? : ");
	getline(cin, str);
	memcpy_s(fee, sizeof(fee), str.c_str(), str.length());
	cin.clear();

	wallet->makeRawTransaction(addr, val, fee);

	_sign_transaction();
}

void _main_routine() {
	//command
	int cmd;

	_main_cmd();

	while (1) {
		cin >> cmd;
		switch (cmd) {
		case 1:
			//1 generateKey;
			_generate_key();
			break;
		case 2:
			//2 saveKey;
			_save_key();
			break;
		case 3:
			//3 loadKey;
			printf("is not working\n");
			break;
			wallet->load();
			break;
		case 4:
			//4 makeTransaction -> sign -> broadcast;
			//4-1 sign inner key;
			//4-2 sign load key;
			_make_raw_transaction();

			break;
		case 5:
			//5 show privKey;
			_show_private_key();
			break;
		case 6:
			//6 show pubKey;
			_show_public_key();
			break;
			//7 broadcast
		case 7:
			break;
			//8 exit;
		case 8:
			exit(1);
			break;
		default:
			printf("다시 입력해주세요\n");
			_main_cmd();
			break;
		}
	}
}

int main() {
	peers = c.to_server().getAddrList();
	sock_serialize _my_peer = peers.end()[-1];
	server s(_my_peer);

	thread *t = new thread(&server::s_server, &s);
	t->join();

	_main_routine();

	return 0;

}