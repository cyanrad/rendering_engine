#include "IOManager.h"
#include <fstream>
#include <iostream>
namespace wangine {
	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			perror(filePath.c_str());
			return false;
		}
		//get file size
		file.seekg(0, std::ios::end);
		int fileSize = file.tellg();

		//go to top
		file.seekg(0, std::ios::beg);

		//reduce file size by header bytes
		fileSize -= file.tellg();

		buffer.resize(fileSize);
		file.read((char*)&(buffer[0]), fileSize);

		file.close();
		return true;
	}
}