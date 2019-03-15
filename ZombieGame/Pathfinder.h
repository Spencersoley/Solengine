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
	glm::vec2 converPositionToCoordinates(glm::vec2 position);

	void updateNeighbourNodes(glm::vec2 nodeCoords, glm::vec2 targetCoords);
	void updateNode(float baseNodeX, float baseNodeY, float updateNodeX, float updateNodeY, glm::vec2 targetCoords, bool isDiag);
	glm::vec2 getLowestf(std::vector<glm::vec2> openSet);

	glm::vec2 m_previousTargetCoords = { 0, 0 };
	std::vector<std::vector<Node>> m_field;
	std::vector<glm::vec2> m_openSet;
	std::vector<glm::vec2> m_closedSet;

	int m_tileWidth;
};

