#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

class Reader {
	private:
		std::string path;
		std::vector<std::byte> buffer;
	public:
		static std::string InputPath();
		Reader(std::string);
		std::string GetPath();
		void SetPath(std::string file);
		std::vector<std::byte> GetInfo();
		void Read();
};
