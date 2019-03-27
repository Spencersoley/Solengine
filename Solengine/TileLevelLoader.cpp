#include "TileLevelLoader.h"

#include <fstream>
#include <iostream>

#include "ErrorHandler.h"
#include "ResourceManager.h"

namespace Solengine
{
	TileLevelLoader::TileLevelLoader()
	{
	}

	TileLevelLoader::~TileLevelLoader()
	{
	}

	//Turns a file into a vector of strings
	std::vector<std::string> TileLevelLoader::ParseLevelData(const std::string& fileName)
	{
		std::ifstream file;
		file.open(fileName);

		if (file.fail())
		{
			Solengine::fatalError(fileName + "would not open");
		}

		std::vector<std::string> levelData;
		std::string temp;
		//To throw away the first string:
		int test;
		file >> temp >> test;
		std::getline(file, temp);
		
		//Will read each line one by one and put it in temp
		while (std::getline(file, temp))
		{
			if (temp.size() > 0) levelData.push_back(temp);
		}
		return levelData;
	}
}
