#pragma once

#include <vector>

#include "Tile.h"

class TileMap
{
public:
	TileMap();
	~TileMap();

	void init(std::vector<std::vector<Tile*>> tileMap, int tileWidth);

	int getWidth() const { return p_tiles[0].size(); }
	int getHeight() const { return p_tiles.size(); }

	std::vector<glm::vec2> getWalkablePos(glm::vec2 coords, int stepsAvailable);
	Tile* getTileByPosition(glm::vec2 pos);	

	void resetWalkable();

	std::vector<std::vector<Tile*>> p_tiles;

	int m_tileWidth;
};

