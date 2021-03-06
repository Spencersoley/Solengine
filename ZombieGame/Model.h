#pragma once

#include <SDL/SDL.h>
//#include <GL/glew.h>
//#include <vector>
//#include <glm/glm.hpp>

#include "Level.h"
#include "Bullet.h"
#include "Player.h"
#include "Zombie.h"

//class Zombie;
class Human;

class Model
{
public:
	Model();
	~Model();

	void init(Player* player, int currentLevel, float physicsSpeed);
	void update(int pauseDuration, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, std::vector<Level*>& levels, std::vector<Bullet>& bullets);
	
	void setNodeField(std::vector<std::vector<Node>> nodeField) { m_defaultNodeField = nodeField; }

private:
	Uint32 getDeltaTicks();
	void updateAgents(float adjustedDeltaTicks, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, std::vector<Level*>& levels, std::vector<Bullet>& bullets);
	void updateBullets(float adjustedDeltaTicks, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, std::vector<Level*>& levels, std::vector<Bullet>& bullets);

	Player* p_player = nullptr;
	std::vector<std::vector<Node>> m_defaultNodeField;

	int m_currentLevel;
	int m_globalFrameCount;
	float m_physicsSpeed;
};

