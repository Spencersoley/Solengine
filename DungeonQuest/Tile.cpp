#pragma once

#include "Tile.h"

Tile::Tile(bool isObstacle, bool isOccupied, int x, int y, int TILE_WIDTH)
{
	m_isObstacle = isObstacle;
	m_isOccupied = isOccupied;
	m_xPos = x * TILE_WIDTH;
	m_yPos = y * TILE_WIDTH;

	m_tileWidth = TILE_WIDTH;

	m_xCoord = x;
	m_yCoord = y;

	m_colour = { 255, 255, 255, 255 };
	m_highlightColour = { 255, 255, 255, 150 };
	m_viableColour = { 0, 255, 0, 100 };

	m_isWalkable = false;
}

Tile::~Tile()
{
}

void Tile::setWalkable(int stepsAvailable)
{
	if (!m_isWalkable)
	{
		m_isWalkable = true;

		stepsAvailable--;

		if (stepsAvailable > 0)
		{
			for (size_t i = 0; i < p_neighbours.size(); i++)
			{
				//if (p_neighbours[i]->m_isObstacle) continue;
				//std::cout << p_neighbours[i]->m_xCoord << std::endl;
				p_neighbours[i]->setWalkable(stepsAvailable);

			}
		}
	}
}