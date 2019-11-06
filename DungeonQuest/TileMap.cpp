#include "TileMap.h"

TileMap::TileMap()
{
}

TileMap::~TileMap()
{
}

void TileMap::Init(std::vector<std::vector<Tile*>> tiles, int tileWidth) 
{
	p_tiles = tiles;
	m_tileWidth = tileWidth;
}

std::vector<glm::vec2> TileMap::GetWalkablePos(glm::ivec2 coords, int steps)
{
	p_tiles[coords.y][coords.x]->SetWalkable(steps + 1, steps + 1);

	std::vector<glm::vec2> walkableTilePos;

	for (size_t y = 0; y < p_tiles.size(); y++)
		for (size_t x = 0; x < p_tiles[0].size(); x++)
            if (!p_tiles[y][x]->GetIsObstacle() && p_tiles[y][x]->GetIsWalkable())
			    walkableTilePos.push_back(p_tiles[y][x]->getPos());

	return walkableTilePos;
}

Tile* TileMap::GetTileByPosition(glm::ivec2 pos)
{
	int x = (int)floor(pos.x / m_tileWidth);
	if (x < 0) return nullptr;
	else if ((size_t)x >= p_tiles[0].size()) return nullptr;

	int y = (int)floor(pos.y / m_tileWidth);
	if (y < 0) return nullptr;
	else if ((size_t)y >= p_tiles.size()) return nullptr;

	if (p_tiles[y][x]->GetIsObstacle()) return nullptr;

	return p_tiles[y][x];
}

void TileMap::ResetWalkable()
{
	for (size_t y = 0; y < p_tiles.size(); y++)
		for (size_t x = 0; x < p_tiles[0].size(); x++)
		{
			p_tiles[y][x]->SetIsWalkable(false);
			p_tiles[y][x]->SetDist(100);
		}
}
