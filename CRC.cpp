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
	for (auto byte : info) {
		std::byte tmp{ 0 };
		for (int i = 0; i < BYTE_SIZE; i++) {
			tmp = byte & mlt;
			tmp >>= BYTE_SIZE - 1;
			buffer <<= 1;
			buffer |= std::bitset<POLY_SIZE>(std::to_integer<int>(tmp));
			if (buffer[POLY_SIZE - 1] == 1) {
				buffer ^= polynomial;
			}
			byte <<= 1;
		}
	}
}

void CRC::ZerosJoining() {
	std::bitset<1> zeroBit{ 0 };
	for (int i = 0; i < POLY_SIZE - 1; i++) {
		buffer <<= 1;
		buffer[0] = zeroBit[0];
		if (buffer[POLY_SIZE - 1] == 1) {
			buffer ^= polynomial;
		}
	}
}

void CRC::Check(std::bitset<POLY_SIZE - 1> sum) {
	if (this->GetChecksum() == sum) {
		std::cout << std::endl << "Verification passed" << std::endl;
	}
	else {
		std::cout << std::endl << "Verification is not passed" << std::endl;
	}
}

std::bitset<POLY_SIZE - 1> CRC::GetChecksum() {
	std::bitset<POLY_SIZE - 1> checkSum;
	for (int i = POLY_SIZE - 2; i >= 0; i--) {
		checkSum[i] = buffer[i];
	}
	return checkSum;
}
