#include "PrCntrl.h"

#include <bitset>

std::ostream& operator<< (std::ostream& stream, std::byte byte) {
	return stream << std::bitset<8>(std::to_integer<int>(byte));
}

std::vector<std::byte> Calc(std::vector<std::byte> info) {
	std::vector<std::byte> result;
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
			result.push_back(std::byte{ 0 });
		}
		else {
			result.push_back(std::byte{ 1 });
		}
	}
	return result;
}

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
			this->checkSum.clear();
			Reader rdr = Reader(Reader::InputPath());
			while (!rdr.IsEnd()) {
				rdr.Read(DEFAULT_PACKAGE);
				CalcDefault(rdr.GetInfo());
			}
			break;
		}

		case 2: {
			if (this->checkSum.empty()) {
				std::cout << "You must calc cheksum first!" << std::endl;
				break;
			}
			PrCntrl inspected = PrCntrl();
			Reader rdr = Reader(Reader::InputPath());
			while (!rdr.IsEnd()) {
				rdr.Read(DEFAULT_PACKAGE);
				inspected.CalcDefault(rdr.GetInfo());
			}
			Check(inspected.GetChecksum());
			break;
		}
		case 3: {
			this->checkSum.clear();
			Reader rdr = Reader(Reader::InputPath());
			while (!rdr.IsEnd()) {
				rdr.Read(VH_PACKAGE_SIZE);
				CalcVerticalHorizontal(rdr.GetInfo());
			}
			break;
		}
		case 4: {
			if (this->checkSum.empty()) {
				std::cout << "You must calc cheksum first!" << std::endl;
				break;
			}
			PrCntrl inspected = PrCntrl();
			Reader rdr = Reader(Reader::InputPath());
			while (!rdr.IsEnd()) {
				rdr.Read(VH_PACKAGE_SIZE);
				inspected.CalcVerticalHorizontal(rdr.GetInfo());
			}
			Check(inspected.GetChecksum());
			break;
		}
		default:
			exit(EXIT_SUCCESS);
		}
	}
}

void PrCntrl::CalcDefault(std::vector<std::byte> info) {
		for (auto value : Calc(info)) {
			this->checkSum.push_back(value);
		}
}

void PrCntrl::Check(std::vector<std::byte> sum) {
	if (this->checkSum == sum) {
		std::cout << std::endl << "Verification passed" << std::endl;
	}
	else {
		std::cout << std::endl << "Verification is not passed" << std::endl;
	}
}

void PrCntrl::CalcVerticalHorizontal(std::vector<std::byte> info) {
	size_t size = info.size();
	if (size % VH_PACKAGE_SIZE != 0) {
		std::byte emptyByte{ 0 };
		for (int i = 0; i < (VH_PACKAGE_SIZE - (size % VH_PACKAGE_SIZE)); i++) {
			auto pos = info.cbegin();
			info.insert(pos + VH_PACKAGE_SIZE * (size / VH_PACKAGE_SIZE), emptyByte);
		}
	}
	std::vector<std::byte> vert;
	for (int j = BYTE_SIZE - 1; j >= 0; j--) {
		std::byte tmp{ 0 };
		int pos = static_cast<int>(pow(2, j));
		std::byte mlt = static_cast<std::byte>(pos);
		for (int i = 0; i < BYTE_SIZE; i++) {
			tmp |= (info[i] & mlt) << BYTE_SIZE - 1 - j >> i;
		}
		vert.push_back(tmp);
	}
	std::vector<std::byte> hChecksum = Calc(info);
	std::vector<std::byte> vChecksum = Calc(vert);
	for (std::byte value : hChecksum) {
		this->checkSum.push_back(value);
	}
	for (std::byte value : vChecksum) {
		this->checkSum.push_back(value);
	}
}

std::vector<std::byte> PrCntrl::GetChecksum() {
	return this->checkSum;
}