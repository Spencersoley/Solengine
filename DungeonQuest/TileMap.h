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

    std::vector<glm::vec2> getWalkablePos(glm::ivec2 coords, int steps);
	Tile* getTileByPosition(glm::ivec2 pos);	
    Tile* getTileByCoords(glm::ivec2 coords) 
	{   
		if (coords.y < p_tiles.size() && coords.x < p_tiles[0].size())
		    return p_tiles[coords.y][coords.x]; 

		return nullptr;
	}

	void resetWalkable();

	std::vector<std::vector<Tile*>> p_tiles;

	int m_tileWidth;
};

