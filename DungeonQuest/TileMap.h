#pragma once

#include <vector>

#include "Tile.h"

class TileMap
{
public:
	TileMap();
	~TileMap();

	void Init(std::vector<std::vector<Tile*>> tileMap, int tileWidth);

	// Getters //
	int GetWidth() const { return p_tiles[0].size(); }
	int GetHeight() const { return p_tiles.size(); }
    std::vector<glm::vec2> GetWalkablePos(glm::ivec2 coords, int steps);
	Tile* GetTileByPosition(glm::ivec2 pos);	
    Tile* GetTileByCoords(glm::ivec2 coords) 
	{   
		if (coords.y < p_tiles.size() && coords.x < p_tiles[0].size())
		    return p_tiles[coords.y][coords.x]; 

		return nullptr;
	}

	void ResetWalkable();

	std::vector<std::vector<Tile*>> p_tiles;

	int m_tileWidth;
};

