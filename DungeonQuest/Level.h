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
	Level(std::vector<std::string> levelData, Solengine::SpriteBatch* batch);
	~Level();

	void draw();

	glm::vec2 getAdeptSpawnCoords() const { return m_adeptSpawnCoords; }
	glm::vec2 getFighterSpawnCoords() const { return m_fighterSpawnCoords; }
	glm::vec2 getScoutSpawnCoords() const { return m_scoutSpawnCoords; }
	int getEnemyCount() const { return m_enemySpawnCoords.size(); }
	glm::vec2 getEnemySpawnCoords(int i) const { return m_enemySpawnCoords[i]; }

	TileMap* getTileMap() { return &m_tileMap; }

	bool checkMouseover(glm::vec2 mousePos) { return false; }

private:
	glm::vec2 m_adeptSpawnCoords;
	glm::vec2 m_fighterSpawnCoords;
	glm::vec2 m_scoutSpawnCoords;
	std::vector<glm::vec2> m_enemySpawnCoords;

	TileMap m_tileMap;
};
