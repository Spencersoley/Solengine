#pragma once

#include "Agent.h"

class Human : public Agent
{
public:
	Human();
	virtual ~Human();

	virtual void move(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime) override;

	void init(float speed, glm::vec2 pos);
	
private: 
	Zombie* getNearestZombie(std::vector<Zombie*>& zombies);
	void redirect();

	Zombie* p_nearestZombie = nullptr;

	int m_turnRate;
};

