#pragma once

#include <SDL/SDL.h>
//#include <GL/glew.h>
//#include <vector>
//#include <glm/glm.hpp>

//class Zombie;
class Human;

class Model
{
public:
	Model();
	~Model();

	void init(float gameSpeed);
	void update(int pauseDuration);

private:
	Uint32 getDeltaTicks();
	void updateAgents(float adjustedDeltaTicks);

	int m_globalFrameCount;
	float m_gameSpeed;
};

