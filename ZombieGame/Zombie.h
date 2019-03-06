#pragma once

#include "Agent.h"

class Zombie : public Agent
{
public:
	Zombie();
	~Zombie();

	void init(float speed, glm::vec2 pos);

	void move(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime) override;


private:
	int m_frames;

	void redirect();

	Human* getNearestHuman(std::vector<Human*>& humans);

	Human* p_nearestHuman = nullptr;
};

