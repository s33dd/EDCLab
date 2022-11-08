#pragma once
#include <vector>

class PrCntrl {
	private:
		std::vector<std::byte> checkSum;
	public:
		PrCntrl();
		void CalcDefault(std::vector<std::byte> info);
		void CheckDefault(std::vector<std::byte> sum);
		void CalcVerticalHorizontal(std::vector<std::byte> info);
		void CheckVerticalHorizontal(std::vector<std::byte> sum);
};
