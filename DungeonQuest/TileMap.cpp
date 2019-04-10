#include "TileMap.h"

TileMap::TileMap(std::vector<std::vector<Tile>> tileMap, int tileWidth) : m_tileMap(tileMap), m_tileWidth(tileWidth)
{
}

TileMap::~TileMap()
{
}

Tile* TileMap::getTileByPosition(glm::vec2 pos)
{
	int x = floor(pos.x / m_tileWidth);
	if (x < 0)
		return nullptr;
	else if (x >= m_tileMap[0].size())
		return nullptr;
	

	int y = floor(pos.y / m_tileWidth);
	if (y < 0)
		return nullptr;
	else if (y >= m_tileMap.size())
		return nullptr;

	if (m_tileMap[y][x].m_isObstacle)
		return nullptr;

	return &m_tileMap[y][x];
}

