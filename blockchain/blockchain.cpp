//// blockchain.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
////
//
//
//#include <iostream>
//#include<vector>
//#include"KISA_SHA256.h"
//
//using namespace std;
//
//int main(int argc, char *argv[])
//{
//
//	unsigned char input[2018] = { "grape" };
//	unsigned char* output1 = new unsigned char[32];
//
//	/*SHA256_INFO sha256_info;
//
//	SHA256_Init(&sha256_info);
//
//	for(int i=0;i<sizeof(input);i++){
//		SHA256_Process(&sha256_info, input, 2018);
//	}
//*/
//	//SHA256_Close(&sha256_info, output1);
//
//	SHA256_Encrpyt(input, sizeof(input), output1);
//
//	for (int i = 0; i < 32; i++) {
//		printf("%02x", output1[i]);
//	}
//	system("pause");
//	return 0;
//}
//
////#include "KISA_SHA256.h"
////
////#include <stdio.h>
////#include <stdlib.h>
////#include <tchar.h>
////
////int main(int argc, char** argv)
////{
////
////	//변수 초기화.
////	FILE *fp = NULL;
////	unsigned char buffer[2048] = { 0, };
////	unsigned char result[32] = { 0, };
////	int read = 0;
////	int loop_number = 0;
////
////	//SHA256 변수 초기화.
////	SHA256_INFO sha256_info;
////
////	SHA256_Init(&sha256_info);
////
////	//파일 읽기.
////	//fp = fopen("Test.txt", "rb"); Visual Studio 옛버전을 사용할 경우. 이것을 사용할 것. Visual Studio에서 안전성 문제로 인한 함수 개선을 하였음.
////	fopen_s(&fp, "Text.txt", "rb");
////
////	if (fp == NULL)
////	{
////		printf("Error : File not find.\n");
////		system("pause");
////		return -1;
////	}
////
////	while ((read = fread(buffer, 2048, 1, fp)) != 0)
////	{
////		SHA256_Process(&sha256_info, buffer, read);
////	}
////
////	SHA256_Close(&sha256_info, result);
////
////	for (loop_number = 0; loop_number < 32; loop_number++)
////	{
////		printf("%02x", result[loop_number]);
////	}
////
////	system("pause");
////	return 0;
////
////}
//
//
