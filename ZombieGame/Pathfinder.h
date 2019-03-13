#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Node.h"

class Pathfinder
{
public:
	Pathfinder();
	~Pathfinder();

	void init(std::vector<std::vector<Node>> nodeField);

	glm::vec2 pathfind(glm::vec2 pos, glm::vec2 target);

private:
	std::vector<std::vector<Node>> m_field;
};

