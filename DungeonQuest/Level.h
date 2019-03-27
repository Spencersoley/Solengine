#pragma once

#include <string>
#include <vector>

#include <Solengine/SpriteBatch.h>

#include "Tile.h"

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
	glm::vec2 getAdeptSpawnCoords() const { return m_adeptSpawnCoords; }

private:
	std::vector<std::string> m_levelData;

	glm::vec2 m_adeptSpawnCoords;

	std::vector<std::vector<Tile>> m_tileMap;

	Solengine::SpriteBatch m_SOL_levelSpriteBatch;
	glm::vec2 m_startPlayerPosition;
	std::vector<glm::vec2> m_startZombiePositions;
};
