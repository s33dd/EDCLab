#include "Reader.h"

std::string Reader::InputPath() {
	std::cout << "Input filename" << std::endl;
	std::string path;
	std::cin >> path;
	return path;
}

Reader::Reader(std::string file) {
	path = file;
}

std::string Reader::GetPath() {
	return this->path;
}

void Reader::SetPath(std::string file) {
	this->path = file;
}

std::vector<std::byte> Reader::GetInfo() {
	return this->buffer;
}

void Reader::Read() {
	std::ifstream fStream(path, std::ios::binary);
	unsigned char tmp;
	if (fStream.is_open()) {
		while (fStream >> tmp) {
			this->buffer.push_back(static_cast<std::byte>(tmp));
		}
	}
	else {
		std::cout << "Filename error" << std::endl;
		exit(EXIT_FAILURE);
	}
}
