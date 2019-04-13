#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <Solengine/Vertex.h>
#include <vector>

class Tile
{
public:
	Tile(bool isObstacle, bool isOccupied, int x, int y, int TILE_WIDTH);
	~Tile();


	bool m_isObstacle;
	bool m_isOccupied;

	bool m_isWalkable;

	int m_xPos;
	int m_yPos;
	int m_xCoord;
	int m_yCoord;

	int m_tileWidth;

	Solengine::ColourRGBA8 m_colour; 
	Solengine::ColourRGBA8 m_highlightColour; 
	Solengine::ColourRGBA8 m_viableColour;

	void addNeighbour(Tile* tile) { p_neighbours.push_back(tile); }
	glm::vec2 getPos() const { return { m_xPos, m_yPos }; }

	void setWalkable(int stepsAvailable);

	std::vector<Tile*> p_neighbours;

private:


};

