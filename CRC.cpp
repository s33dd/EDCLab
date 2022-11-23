#include "CRC.h"

CRC::CRC() {
	polynomial = 0x864CFB;
	buffer = 0;
}

void CRC::Chosen() {
	int choice;
	while (true) {
		std::cout << std::endl << "Choose what are you want to do:" << std::endl <<
			"1 - Calculate checksum" << std::endl << "2 - Check file" << std::endl;
		std::cin >> choice;
		switch (choice) {
		case 1: {
			this->buffer = 0;
			Reader rdr = Reader(Reader::InputPath());
			while (!rdr.IsEnd()) {
				rdr.Read(PACKAGE);
				Calc(rdr.GetInfo());
			}
			ZerosJoining();
			std::cout << GetChecksum() << std::endl;
			break;
		}

		case 2: {
			if (this->buffer == 0) {
				std::cout << "You must calc checksum first!" << std::endl;
				break;
			}
			CRC inspected = CRC();
			Reader rdr = Reader(Reader::InputPath());
			while (!rdr.IsEnd()) {
				rdr.Read(PACKAGE);
				inspected.Calc(rdr.GetInfo());
			}
			inspected.ZerosJoining();
			Check(inspected.GetChecksum());
			break;
		}
		default:
			exit(EXIT_SUCCESS);
		}
	}
}

void CRC::Calc(std::vector<std::byte> info) {
	std::byte mlt{ 128 }; // byte {1000 0000} for taking the leftmost bit
	bool isXOR = false;
	for (auto byte : info) {
		std::byte tmp{ 0 };
		for (int i = 0; i < BYTE_SIZE; i++) {
			tmp = byte & mlt;
			tmp >>= BYTE_SIZE - 1;
			if (buffer[POLY_SIZE-1] == 1) {
				isXOR = true;
			}
			buffer <<= 1;
			buffer |= std::bitset<POLY_SIZE>(std::to_integer<int>(tmp));
			if (isXOR) {
				buffer ^= polynomial;
			}
			isXOR = false;
			byte <<= 1;
		}
	}
}

void CRC::ZerosJoining() {
	std::bitset<1> zeroBit{ 0 };
	bool isXOR = false;
	for (int i = 0; i < POLY_SIZE; i++) {
		if (buffer[POLY_SIZE - 1] == 1) {
			isXOR = true;
		}
		buffer <<= 1;
		buffer[0] = zeroBit[0];
		if (isXOR) {
			buffer ^= polynomial;
		}
		isXOR = false;
	}
}

void CRC::Check(std::bitset<POLY_SIZE> sum) {
	if (this->GetChecksum() == sum) {
		std::cout << std::endl << "Verification passed" << std::endl;
	}
	else {
		std::cout << std::endl << "Verification is not passed" << std::endl;
	}
}

std::bitset<POLY_SIZE> CRC::GetChecksum() {
	std::bitset<POLY_SIZE> checkSum;
	for (int i = POLY_SIZE - 1; i >= 0; i--) {
		checkSum[i] = buffer[i];
	}
	return checkSum;
}
