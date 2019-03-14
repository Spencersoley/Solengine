#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Node.h"

class Pathfinder
{
public:
	Pathfinder();
	~Pathfinder();

	void init(std::vector<std::vector<Node>> nodeField, int tileWidth);

	glm::vec2 pathfind(glm::vec2 pos, glm::vec2 target);

private:	
	glm::vec2 getCoordinates(glm::vec2 position);

	void updateNeighbourNodes(glm::vec2 nodeCoords);

	glm::vec2 m_previousTargetCoords = { 0, 0 };
	std::vector<std::vector<Node>> m_field;
	std::vector<glm::vec2> openSet;
	std::vector<glm::vec2> closedSet;

	int m_tileWidth;
};

