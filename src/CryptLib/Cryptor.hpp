#pragma once

#include <string>
#include <iostream>

// Algoritm: "XOR encryption"

#define ROUND_COUNT 4

namespace cryptor::RemoweEX {
	std::wstring RemoweEX(std::wstring STR, std::wstring File_Extension);
	std::string RemoweEX(std::string STR, std::string File_Extension);
}

namespace cryptor::splitNumber {
	unsigned long long MergeNums(unsigned NumA, unsigned NumB);
	unsigned GetLeft(unsigned long long Num);
	unsigned GetRight(unsigned int long long Num);
}

namespace cryptor {
	typedef unsigned char		BYTE;
	typedef BYTE* p_BYTE;

	typedef unsigned long long	KEY_TYPE;
	typedef p_BYTE				DATA_TYPE;

	struct seed_t {
		unsigned x = 100;
		unsigned y = 35;
		unsigned z = 4;
		unsigned w = 0;
	};

	unsigned XorShift128();

	DATA_TYPE Crypt(const KEY_TYPE KEY, const DATA_TYPE DATA, const size_t DATA_SIZE);
	DATA_TYPE DeCrypt(const KEY_TYPE KEY, const DATA_TYPE DATA, const size_t DATA_SIZE);
	KEY_TYPE GenerateKEY(const KEY_TYPE DATA);
	bool KEYIsCorrect(const KEY_TYPE KEY);
}