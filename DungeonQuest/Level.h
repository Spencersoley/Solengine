#pragma once

#include <string>
#include <vector>

#include <Solengine/SpriteBatch.h>

#include "Tile.h"
#include "TileMap.h"

const int TILE_WIDTH = 64;

class Level
{
public:
	//Load the level
	Level(std::vector<std::string> levelData, Solengine::SpriteBatch* spriteBatch);
	~Level();

	glm::vec2 getAdeptSpawnCoords() const { return m_adeptSpawnCoords; }
	glm::vec2 getFighterSpawnCoords() const { return m_fighterSpawnCoords; }
	glm::vec2 getScoutSpawnCoords() const { return m_scoutSpawnCoords; }
	glm::vec2 getRatSpawnCoords() const { return m_ratSpawnCoords; }

	TileMap* getTileMap() { return &m_tileMap; }

	Solengine::SpriteBatch* getSpriteBatch() { return p_SOL_SB; }

private:
	glm::vec2 m_adeptSpawnCoords;
	glm::vec2 m_fighterSpawnCoords;
	glm::vec2 m_scoutSpawnCoords;
	glm::vec2 m_ratSpawnCoords;

	TileMap m_tileMap;

	Solengine::SpriteBatch* p_SOL_SB;
};
