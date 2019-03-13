#include "Pathfinder.h"

#include <iostream>

Pathfinder::Pathfinder()
{
}

Pathfinder::~Pathfinder()
{
}

void Pathfinder::init(std::vector<std::vector<Node>> nodeField)
{
	m_field = nodeField;
}

glm::vec2 Pathfinder::pathfind(glm::vec2 pos, glm::vec2 target)
{
	glm::vec2 dir = { 0, 0 };

	//
	// m_field;

	//m_field[][]

	std::cout << pos.x << " " << pos.y << std::endl;

	return dir;
}
