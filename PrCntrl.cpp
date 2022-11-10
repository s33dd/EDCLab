#include "PrCntrl.h"


PrCntrl::PrCntrl() {
	checkSum.clear();
}

void PrCntrl::Chosen() {
	int choice;
	while (true) {
		std::cout << std::endl << "Choose what are you want to do:" << std::endl <<
			"1 - Default parity control calculate" << std::endl << "2 - Default parity control check" <<
			std::endl << "3 - Vertical and horizontal parity control calculate" << std::endl <<
			"4 - Vertical and horizontal parity control check" << std::endl;
		std::cin >> choice;
		switch (choice) {
		case 1: {
			Reader rdr = Reader(Reader::InputPath());
			rdr.Read();
			CalcDefault(rdr.GetInfo());
			break;
		}

		case 2: {
			if (this->checkSum.empty()) {
				std::cout << "You must calc cheksum first!" << std::endl;
				break;
			}
			Reader rdr = Reader(Reader::InputPath());
			rdr.Read();
			PrCntrl inspected = PrCntrl();
			inspected.CalcDefault(rdr.GetInfo());
			CheckDefault(inspected.GetChecksum());
			break;
		}
		case 3:
			//Call reader
			//CalcVerticalHorizontal();
			//break;
		case 4: {
			//Call reader
			//PrCntrl inspected = PrCntrl();
			//inspected.CalcDefault();
			//CheckVerticalHorizontal();
			//break;
		}
		default:
			exit(EXIT_SUCCESS);
		}
	}
}

void PrCntrl::CalcDefault(std::vector<std::byte> info) {
	for (auto byte : info) {
		int count = 0;
		std::byte multiplier { 1 };
		for (int i = 0; i < BYTE_SIZE; i++) {
			bool result = static_cast<bool>(byte & multiplier);
			if (result) {
				count++;
			}
			byte >>= 1;
		}
		if (count % 2 == 0) {
			this->checkSum.push_back(std::byte{ 0 });
		}
		else {
			this->checkSum.push_back(std::byte{ 1 });
		}
	}
}

void PrCntrl::CheckDefault(std::vector<std::byte> sum) {
	if (this->checkSum == sum) {
		std::cout << "Verification passed" << std::endl;
	}
	else {
		std::cout << std::endl << "Verification is not passed" << std::endl;
	}
}

void PrCntrl::CalcVerticalHorizontal(std::vector<std::byte> info) {
	if (info.size() % PACKAGE_SIZE != 0) {
		std::byte emptyByte{ 0 };
		for (int i = 0; i < (PACKAGE_SIZE - (info.size() % PACKAGE_SIZE)); i++) {
			auto pos = info.cbegin();
			info.insert(pos, emptyByte);
		}
	}
	while (!info.empty()) {
		std::vector<std::byte> package;
		for (int i = 0; i < PACKAGE_SIZE; i++) {
			package.push_back(info[i]);
		}

	}
}

std::vector<std::byte> PrCntrl::GetChecksum() {
	return this->checkSum;
}
