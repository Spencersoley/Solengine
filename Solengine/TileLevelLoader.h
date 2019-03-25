#pragma once

#include <string>
#include <vector>

namespace Solengine
{
	class TileLevelLoader
	{
	public:
		TileLevelLoader();
		~TileLevelLoader();

		std::vector<std::string> ParseLevelData(const std::string& fileName);
	};
}