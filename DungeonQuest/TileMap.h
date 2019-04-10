#pragma once

#include <vector>

#include "Tile.h"

class TileMap
{
public:
	TileMap(std::vector<std::vector<Tile>> tileMap, int tileWidth);
	~TileMap();

	int getWidth() const { return m_tileMap[0].size(); }
	int getHeight() const { return m_tileMap.size(); }

	Tile* getTileByPosition(glm::vec2 pos);
	
	std::vector<std::vector<Tile>> m_tileMap;
	int m_tileWidth;

};

