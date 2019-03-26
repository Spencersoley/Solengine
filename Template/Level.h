#pragma once

#include <string>
#include <vector>

#include <Solengine/SpriteBatch.h>

const int TILE_WIDTH = 64;

class Level
{
public:
	//Load the level
	Level(std::vector<std::string> levelData);
	~Level();

	void draw();

	int getWidth() const { return m_levelData[0].size(); } //nts: It's a vector of strings. Width is the size of the string, height is the number of strings
	int getHeight() const { return m_levelData.size(); }

private:
	std::vector<std::string> m_levelData;

	Solengine::SpriteBatch m_SOL_levelSpriteBatch;
	glm::vec2 m_startPlayerPosition;
	std::vector<glm::vec2> m_startZombiePositions;
};
