#pragma once

#include <string>
#include <glm/glm.hpp>
#include <vector>

#include "Bullet.h"

class Gun
{
public:
	Gun(std::string name, int fireRate, int bulletsPerShot, float spread, float bulletDamage, float bulletSpeed);
	~Gun();

	void update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets, float adjustedDeltaTicks);
	void reload();

private:
	void fire(const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets);
	
	std::string m_name;
	int m_fireRate; //in terms of frames
	int m_bulletsPerShot; //How many bullets fired at a time
	float m_spread; //accuracy
	float m_bulletDamage;
	float m_bulletSpeed;
	float m_frameCounter; //move to stack?
};

