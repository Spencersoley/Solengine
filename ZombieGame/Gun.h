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

	void update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets, float deltaTime);
	void reload();

private:

	void fire(const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets);
	
	std::string _name;
	int _fireRate; //in terms of frames
	int _bulletsPerShot; //How many bullets fired at a time
	float _spread; //accuracy
	float _bulletDamage;
	float _bulletSpeed;


	float _frameCounter;
};

