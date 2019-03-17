#pragma once

#include "Agent.h"

#include "Pathfinder.h"

class Zombie : public Agent
{
public:
	Zombie();
	~Zombie();

	void init(float speed, glm::vec2 pos, std::vector<std::vector<Node>> nodeField);

	void move(float adjustedDeltaTicks, int globalFrameCount, std::vector<Human*>& humans, std::vector<Zombie*>& zombies) override;

private:
	Human* getNearestHuman(std::vector<Human*>& humans);
	void redirect();

	Human* p_nearestHuman = nullptr;

	Pathfinder m_pathfinder;
};

