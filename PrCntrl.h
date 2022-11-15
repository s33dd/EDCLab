#pragma once
#include <vector>
#include <iostream>
#include "Reader.h"
#define BYTE_SIZE 8
#define VH_PACKAGE_SIZE 8
#define DEFAULT_PACKAGE 1

class PrCntrl {
	private:
		std::vector<std::byte> checkSum;
	public:
		PrCntrl();
		void Chosen();
		void CalcDefault(std::vector<std::byte> info);
		void Check(std::vector<std::byte> sum);
		void CalcVerticalHorizontal(std::vector<std::byte> info);
		std::vector<std::byte> GetChecksum();
};
