#pragma once

#include "Human.h"

#include <Solengine/InputManager.h>
#include <Solengine/Camera2D.h>

#include "Bullet.h"

#include <iostream>

//#include "Gun.h"
class Gun;

class Player : public Human
{
public:
	Player();
	~Player();

	void init(float speed, glm::vec2 pos);
	void setCamera(Solengine::Camera2D* cam) { p_cam = cam; }
	void addGun(Gun* gun);
	void move(float adjustedDeltaTicks, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, std::vector<Bullet>& bullets); //Why can we override this but not zombie/human's move
	
	void setYDir(int dir) { m_direction.y += dir; }
	void setXDir(int dir) { m_direction.x += dir; }
	int getNumOfGuns() { return p_guns.size(); }
	int getCurrentGunIndex() { return m_currentGunIndex; }
	void setCurrentGunIndex(int index) { m_currentGunIndex = index; while (m_currentGunIndex > (int)p_guns.size()) m_currentGunIndex--; }
	void setMouseCoords(glm::vec2 mouseCoords) { m_mouseCoords = mouseCoords; }
	void setIsMouseDown(bool mouseDown) { m_isMouseDown = mouseDown;  }

private:
	std::vector<Gun*> p_guns;
	Solengine::Camera2D* p_cam = nullptr;

	int m_currentGunIndex;
	glm::vec2 m_direction;
	bool m_isMouseDown;
	glm::vec2 m_mouseCoords;
};

