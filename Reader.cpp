#include "Reader.h"

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
	while(fStream >> tmp) {
		this->buffer.push_back(static_cast<std::byte>(tmp));
	}
}
