#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <list>

#include "Node.h"

class Pathfinder
{
public:
	Pathfinder();
	~Pathfinder();

	void pathfind(glm::vec2 pos, glm::vec2 target);
	glm::vec2 getDirectionToNextNode(glm::vec2 startPos);

	void setNodeField(std::vector<std::vector<Node>> nodeField) { m_field = nodeField; }
	void setTileWidth(int tileWidth) { m_tileWidth = tileWidth; }

private:	
	glm::ivec2 convertPositionToCoordinates(glm::vec2 position);

	void updateNeighbourNodes(glm::ivec2 nodeCoords, glm::ivec2 targetCoords);
	void updateNode(int baseNodeX, int baseNodeY, int updateNodeX, int updateNodeY, glm::ivec2 targetCoords, int addedG);
	glm::ivec2 getLowestF();

	glm::ivec2 m_previousTargetCoords = { 0, 0 };
	glm::ivec2 m_previousStartCoords = { 0, 0 };
	std::vector<std::vector<Node>> m_field;
	std::vector<glm::ivec2> m_openList;
	std::vector<glm::ivec2> m_closedList;

	int m_tileWidth;
};

