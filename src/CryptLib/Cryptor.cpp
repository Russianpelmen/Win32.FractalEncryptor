#include "Cryptor.hpp"

namespace cryptor::RemoweEX {
	std::wstring RemoweEX(std::wstring STR, std::wstring File_Extension) {
		if (STR.find(File_Extension)) {
			STR[STR.length() - File_Extension.length()] = '\0';
			return STR;
		}

		return STR;
	}

	std::string RemoweEX(std::string STR, std::string File_Extension) {
		if (STR.find(File_Extension)) {
			STR[STR.length() - File_Extension.length()] = '\0';
			return STR;
		}

		return STR;
	}
}

namespace cryptor::splitNumber {

	unsigned long long MergeNums(unsigned NumA, unsigned NumB) {
		return ((unsigned long long)NumA << 32) | NumB;
	}

	unsigned GetLeft(unsigned long long Num) {
		return (unsigned)(Num >> 32);
	}

	unsigned GetRight(unsigned int long long Num) {
		return (unsigned)Num;
	}

}

namespace cryptor {
	const unsigned CheckKeyNum = 0xFFFFFFFF;

	typedef unsigned char		BYTE;
	typedef BYTE* p_BYTE;

	typedef unsigned long long	KEY_TYPE;
	typedef p_BYTE				DATA_TYPE;

	unsigned XorShift128() {
		static seed_t s;

		unsigned t = s.x ^ (s.x << 11);
		s.x = s.y;
		s.y = s.z;
		s.z = s.w;
		s.w = (s.w ^ (s.w >> 19)) ^ (t ^ (t >> 8));

		return s.w;
	}

	DATA_TYPE Crypt(const KEY_TYPE KEY, const DATA_TYPE DATA, const size_t DATA_SIZE) {
		DATA_TYPE New_data = new BYTE[DATA_SIZE];
		std::memcpy(New_data, DATA, DATA_SIZE);

		for (short round_n = 0; round_n <= ROUND_COUNT; round_n++) {
			for (size_t i = 0; i < DATA_SIZE; i++) {
				New_data[i] ^= KEY;
				New_data[i] = static_cast<BYTE>(New_data[i] + (i % 256));
			}
		}

		return New_data;
	}

	DATA_TYPE DeCrypt(const KEY_TYPE KEY, const DATA_TYPE DATA, const size_t DATA_SIZE) {
		DATA_TYPE new_data = new BYTE[DATA_SIZE];
		std::memcpy(new_data, DATA, DATA_SIZE);

		for (short round_n = 0; round_n <= ROUND_COUNT; round_n++) {
			for (size_t i = 0; i < DATA_SIZE; i++) {
				new_data[i] = static_cast<BYTE>(new_data[i] - (i % 256));
				new_data[i] ^= KEY;
			}
		}

		return new_data;
	}

	KEY_TYPE GenerateKEY(const KEY_TYPE DATA) {
		unsigned RightKeyPart = splitNumber::GetRight(DATA);

		return splitNumber::MergeNums(CheckKeyNum ^ RightKeyPart, RightKeyPart);
	}

	bool KEYIsCorrect(const KEY_TYPE KEY) {
		unsigned RightKeyPart = splitNumber::GetRight(KEY);
		unsigned LeftKeyPart = splitNumber::GetLeft(KEY) ^ RightKeyPart;

		return (LeftKeyPart == CheckKeyNum) ? true : false;
	}
}