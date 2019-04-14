#pragma once

#include <Solengine/Vertex.h>

#include <glm/glm.hpp>
#include <iostream>
#include <vector>

class Tile
{
public:
	Tile(bool isObstacle, bool isOccupied, int x, int y, int TILE_WIDTH);
	~Tile();

	bool m_isObstacle;
	bool m_isOccupied;

	bool m_isWalkable;
	int m_stepDistance;

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

	int getDist() { return m_stepDistance; }
	void setDist(int dist) { m_stepDistance = dist; }
	bool getIsObstacle() { return m_isObstacle; }
	void setIsObstacle(bool set) { m_isObstacle = set; }
	bool getIsWalkable() { return m_isWalkable; }
	void setIsWalkable(bool set) { m_isWalkable = set; }

	void setWalkable(int stepsAvailable, int stepDistance);
	void setOccupied(bool occupied) { m_isOccupied = occupied; }

	std::vector<Tile*> p_neighbours;

private:

};