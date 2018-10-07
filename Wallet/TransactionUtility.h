#pragma once

#include<iostream>
#include<Windows.h>
#include<cstring>
#include"sha.h"
#include"filters.h"
#include"hex.h"
#include"base64.h"
#include<sstream>
#include<string>

using namespace CryptoPP;
using namespace std;

namespace TransactionUtility {

	class TxUtil {
	public:
		void getTime(PUCHAR &src) {
			SYSTEMTIME utc;
			SYSTEMTIME cur_time;
			TIME_ZONE_INFORMATION tzi;
			GetSystemTime(&utc);
			GetTimeZoneInformation(&tzi);
			SystemTimeToTzSpecificLocalTime(&tzi, &utc, &cur_time);
			
			stringstream tss;

			tss << to_string(cur_time.wYear);
			tss << to_string(cur_time.wMonth);
			tss << to_string(cur_time.wDay);
			tss << to_string(cur_time.wHour);
			tss << to_string(cur_time.wMinute);
			tss << to_string(cur_time.wSecond);
			tss << to_string(cur_time.wMilliseconds);

			memcpy_s(src, _msize(src), tss.str().c_str(), tss.str().length());

		};

		void calculateHash(PUCHAR & hash, 
					const PUCHAR & addr, 
					const PUCHAR & val, 
					const PUCHAR & fee, 
					const PUCHAR & sMsg, 
					const PUCHAR & time) {
			
			string digest;
			SHA256 sha256;

			stringstream input;
			input << hash << addr << val << fee << sMsg << time;

			StringSource ss(input.str(), true, new HashFilter(sha256, new HexEncoder(new StringSink(digest))));

			memcpy_s(hash, _msize(hash), digest.c_str(), digest.length());
		};

		void calculateHash(PUCHAR & hash, const PUCHAR & pervHash, const PUCHAR & merkleRootHash, const PUCHAR & time, const UINT & diff, const UINT & nonce) {

			SHA256 sha256;
			string digest;
			stringstream input;

			input << hash << pervHash << merkleRootHash << time << diff << nonce;

			StringSource ss(input.str(), true, new HashFilter(sha256, new HexEncoder(new StringSink(digest))));

			memcpy_s(hash, _msize(hash), digest.c_str(), digest.length());

		};

		void calculateHash(PUCHAR & src) {
			
			string digest;
			SHA256 sha256;

			stringstream input;

			input << src;

			StringSource ss(input.str(), true, new HashFilter(sha256, new HexEncoder(new StringSink(digest))));

			memcpy_s(src, _msize(src), digest.c_str(), digest.length());

		};

		void add(PUCHAR & dest, const PUCHAR & src) {
		
			size_t src_size = _msize(src)/sizeof(char);
			size_t dest_size = _msize(dest)/sizeof(char);

			for (int i = 0; i < src_size; i++) {
				dest[i + dest_size] = src[i];
			}

			dest[src_size + dest_size] = '\0';

		};
	};
}