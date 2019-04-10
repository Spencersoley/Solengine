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

	void init(float physicsSpeed);
	void update(int pauseDuration, std::vector<Unit*> units, Unit* currentUnit);
	void setTileMap(TileMap* tileMap) { p_tileMap = tileMap; }

private:
	Uint32 getDeltaTicks();
	void updateAgents(float adjustedDeltaTicks);

	float m_physicsSpeed;


	TileMap* p_tileMap;
};

