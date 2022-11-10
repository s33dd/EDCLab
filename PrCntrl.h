#pragma once
#include <vector>
#include <iostream>
#include "Reader.h"
#define BYTE_SIZE 8
#define PACKAGE_SIZE 8

class PrCntrl {
	private:
		std::vector<std::byte> checkSum;
	public:
		PrCntrl();
		void Chosen();
		void CalcDefault(std::vector<std::byte> info);
		void CheckDefault(std::vector<std::byte> sum);
		void CalcVerticalHorizontal(std::vector<std::byte> info);
		void CheckVerticalHorizontal(std::vector<std::byte> sum);
		std::vector<std::byte> GetChecksum();
};
