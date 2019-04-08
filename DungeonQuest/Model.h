#pragma once

#include <SDL/SDL.h>
//#include <GL/glew.h>
//#include <vector>
//#include <glm/glm.hpp>
#include "Unit.h"
//class Zombie;

class Model
{
public:
	Model();
	~Model();

	void init(float physicsSpeed, int* turnCounter, Unit* currentUnit);
	void update(int pauseDuration);

private:
	Uint32 getDeltaTicks();
	void updateAgents(float adjustedDeltaTicks);

	int m_globalFrameCount;
	float m_physicsSpeed;
};

