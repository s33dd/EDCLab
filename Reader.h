#pragma once
#include <fstream>
#include <string>
#include <vector>

class Reader {
	private:
		std::string path;
		std::vector<std::byte> buffer;
	public:
		Reader(std::string);
		std::string GetPath();
		void SetPath(std::string file);
		std::vector<std::byte> GetInfo();
		void Read();
};
