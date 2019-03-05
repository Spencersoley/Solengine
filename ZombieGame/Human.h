#pragma once

#include "Agent.h"

class Human : public Agent
{
public:
	Human();
	virtual ~Human();

	void init(float speed, glm::vec2 pos);
	
	virtual void move(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime) override;



private: 
	int _turnRate;
	int _frameCount;

	void redirect();


	Zombie* getNearestZombie(std::vector<Zombie*>& zombies);

	Zombie* _nearestZombie = nullptr;
};

