#pragma once

#include <vector>
#include <string>
//No constructor/destructor, so this is a static class. There's only ever going to be one instance of the methods.
//This is because we'll only need one IO manager. 

namespace Solengine
{
	class IOManager
	{
	public:
		static std::vector<unsigned char> ReadFileToBuffer(std::string filePath);
	};
}

