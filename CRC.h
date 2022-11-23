#pragma once
#include <vector>
#include <iostream>
#include <bitset>
#include "Reader.h"
#define POLY_SIZE 24
#define BYTE_SIZE 8
#define PACKAGE 3

class CRC {
private:
	std::bitset<POLY_SIZE> polynomial;
	std::bitset<POLY_SIZE> buffer;
public:
	CRC();
	void Chosen();
	void Calc(std::vector<std::byte> info);
	void ZerosJoining();
	void Check(std::bitset<POLY_SIZE> sum);
	std::bitset<POLY_SIZE> GetChecksum();
};

