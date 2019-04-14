#include "Tile.h"

Tile::Tile(bool isObstacle, bool isOccupied, int x, int y, int TILE_WIDTH)
{
	m_isObstacle = isObstacle;
	m_isOccupied = isOccupied;
	m_stepDistance = 9;
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

void Tile::setWalkable(int stepsAvailable, int stepTotal)
{	
	if (stepsAvailable > 0)
	{
		m_isWalkable = true;
	
		int newDistance = stepTotal - stepsAvailable;
		if (newDistance < m_stepDistance) m_stepDistance = newDistance;
		
		int step = --stepsAvailable;
	    for (size_t i = 0; i < p_neighbours.size(); i++)
			if (!p_neighbours[i]->m_isOccupied)
	            p_neighbours[i]->setWalkable(step, stepTotal);
	}
}