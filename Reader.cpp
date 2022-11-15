#include "Reader.h"

std::string Reader::InputPath() {
	std::cout << "Input filename" << std::endl;
	std::string path;
	std::cin >> path;
	return path;
}

Reader::Reader(std::string file) {
	path = file;
	std::ifstream fStream(path, std::ios::binary);
	if (!fStream.is_open()) {
		std::cout << "Filename error" << std::endl;
		exit(EXIT_FAILURE);
	}
	fStream.seekg(0, fStream.end);
	length = fStream.tellg();
	fStream.seekg(0, fStream.beg);
	position = fStream.tellg();
	fStream.close();
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

void Reader::Read(int size) {
	buffer.clear();
	fStream.open(path);
	unsigned char tmp;
	if (fStream.is_open()) {
		fStream.seekg(position);
		for(int i = 0; i < size; i++) {
			fStream >> tmp;
			this->buffer.push_back(static_cast<std::byte>(tmp));
			if (fStream.tellg() == length) {
				position = length;
				return;
			}
		}
	}
	else {
		std::cout << "Filename error" << std::endl;
		exit(EXIT_FAILURE);
	}
	position = fStream.tellg();
	fStream.close();
}

bool Reader::IsEnd() {
	return position == length;
}
