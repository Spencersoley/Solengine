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

	int GetDist() { return m_stepDistance; }
	void SetDist(int dist) { m_stepDistance = dist; }
	bool GetIsObstacle() { return m_isObstacle; }
	void SetIsObstacle(bool set) { m_isObstacle = set; }
	bool GetIsWalkable() { return m_isWalkable; }
	void SetIsWalkable(bool set) { m_isWalkable = set; }

	void SetWalkable(int stepsAvailable, int stepDistance);
	void SetOccupied(bool occupied) { m_isOccupied = occupied; }

	std::vector<Tile*> p_neighbours;

private:

};