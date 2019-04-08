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
	Level(std::vector<std::string> levelData, Solengine::SpriteBatch* spriteBatch);
	~Level();

	int getWidth() const { return m_levelData[0].size(); } //nts: It's a vector of strings. Width is the size of the string, height is the number of strings
	int getHeight() const { return m_levelData.size(); }
	glm::vec2 getAdeptSpawnCoords() const { return m_adeptSpawnCoords; }
	glm::vec2 getFighterSpawnCoords() const { return m_fighterSpawnCoords; }
	glm::vec2 getScoutSpawnCoords() const { return m_scoutSpawnCoords; }	
	glm::vec2 getRatSpawnCoords() const { return m_ratSpawnCoords; }

	Solengine::SpriteBatch* getSpriteBatch() { return p_SOL_SB; }

private:
	std::vector<std::string> m_levelData;

	glm::vec2 m_adeptSpawnCoords;
	glm::vec2 m_fighterSpawnCoords;
	glm::vec2 m_scoutSpawnCoords;
	glm::vec2 m_ratSpawnCoords;

	std::vector<std::vector<Tile>> m_tileMap;

	Solengine::SpriteBatch* p_SOL_SB;

	glm::vec2 m_startPlayerPosition;

};
