#pragma once

#include <glm/glm.hpp>
#include <iostream>

struct Tile
{
	Tile(bool isObstacle, bool isOccupied, int x, int y, int TILE_WIDTH)
	{
		m_isObstacle = isObstacle;
		m_isOccupied = isOccupied;
		m_xPos = x * TILE_WIDTH;
		m_yPos = y * TILE_WIDTH;

		m_tileWidth = TILE_WIDTH;

		m_xCoord = x;
		m_yCoord = y;
	}
	~Tile()
	{
	}

	bool m_isObstacle;
	bool m_isOccupied;

	int m_xPos;
	int m_yPos;
	int m_xCoord;
	int m_yCoord;

	int m_tileWidth;
};

