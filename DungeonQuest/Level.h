#pragma once

#include <string>
#include <vector>

#include <Solengine/SpriteBatch.h>

#include "Drawable.h"
#include "TileMap.h"

const int TILE_WIDTH = 64;

class Level : public Drawable
{
public:
	//Load the level
	Level(std::vector<std::string> levelData);
	~Level();

	void Draw();

	glm::vec2 GetAdeptSpawnCoords() const { return m_adeptSpawnCoords; }
	glm::vec2 GetFighterSpawnCoords() const { return m_fighterSpawnCoords; }
	glm::vec2 GetScoutSpawnCoords() const { return m_scoutSpawnCoords; }
	int GetEnemyCount() const { return m_enemySpawnCoords.size(); }
	glm::vec2 GetEnemySpawnCoords() 
	{ 
		glm::vec2 spawnCoords = m_enemySpawnCoords[m_enemySpawnCoords.size() - 1];
		m_enemySpawnCoords.pop_back();
		return spawnCoords; 
	}

	TileMap* GetTileMap() { return &m_tileMap; }

	bool CheckMouseover(glm::vec2 mousePos) { return false; }

private:
	glm::vec2 m_adeptSpawnCoords;
	glm::vec2 m_fighterSpawnCoords;
	glm::vec2 m_scoutSpawnCoords;
	std::vector<glm::vec2> m_enemySpawnCoords;

	TileMap m_tileMap;
};
