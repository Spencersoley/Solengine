#pragma once

#include <glm/glm.hpp>
#include <iostream>

struct Tile
{
	Tile(bool obstacle, int x, int y, int TILE_WIDTH)
	{
		m_obstacle = obstacle;
		m_xPos = x * TILE_WIDTH;
		m_yPos = y * TILE_WIDTH;

		m_tileWidth = TILE_WIDTH;

		m_xCoord = x;
		m_yCoord = y;
	}
	~Tile()
	{
	}


	bool m_obstacle;


	int m_xPos;
	int m_yPos;
	int m_xCoord;
	int m_yCoord;
	//* p_parent = nullptr;
	int m_tileWidth;
};

