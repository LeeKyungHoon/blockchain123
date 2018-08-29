

#include"blockchain.h"
#include"wallet.h"

#include<thread>




#include <windows.h>
#include <wininet.h>
#include<string>
#include<iostream>


void __mining(void) {
	while (running_flag) {
		Blockchain::GetInstance()->makeNewBlock();
		Blockchain::GetInstance()->mineBlock();
	}
}

void __chain_main(Blockchain *blockchain) {



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
			break;
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

int main(void) {
	//Wallet * wallet = Wallet::GetInstance();
	//Blockchain * blockchain = Blockchain::GetInstance();

	//std::thread*p1Thread = new std::thread(__wallet_main, wallet, blockchain);
	//std::thread*p2Thread = new std::thread(__mining);

	//p1Thread->join();
	//p2Thread->join();
	//__wallet_main(wallet, blockchain);
	//__blockchain_main(blockchain);



	system("pause");
	return 0;
}