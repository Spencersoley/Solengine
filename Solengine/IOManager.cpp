#include "IOManager.h"

#include <fstream>

namespace Solengine
{
	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			perror(filePath.c_str());
			return false;
		}

		//seek to the end
		file.seekg(0, std::ios::end);

		//Get the file size
		std::streamoff fileSize = file.tellg();

		//seek to beginning 
		file.seekg(0, std::ios::beg);

		//Reduce file size by any present header bytes
		fileSize -= file.tellg();

		buffer.resize((const unsigned int)fileSize);
		file.read((char *)&(buffer[0]), fileSize);
		file.close();

		return true;
	}
}