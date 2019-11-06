#include "IOManager.h"

#include <fstream>
#include <iostream>

#include "ErrorManager.h"

namespace Solengine
{
	std::vector<unsigned char> IOManager::ReadFileToBuffer(std::string filePath)
	{
		std::vector<unsigned char> buffer;

		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			perror(filePath.c_str());
			ErrorManager::FatalError("Failed to load PNG file to buffer!");
		    return buffer;
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

		return buffer;
	}
}