#pragma once

#include <glm/glm.hpp>

#include <Solengine/SpriteBatch.h>

class Human;
class Zombie;
class Agent;

const int BULLET_RADIUS = 5;

class Bullet
{
public:
	Bullet(glm::vec2 pos, glm::vec2 dir, float damage, float speed);
	~Bullet();

	void draw(Solengine::SpriteBatch& spriteBatch);

	bool collisionWithAgent(Agent* agent);

	bool collisionWithWorld(const std::vector<std::string>& levelData);

	void move(float deltaTime);

	float getDamage() const { return _damage; }

private:	

	int _id;
	int _lifeTime;

	glm::vec2 _position;
	glm::vec2 _direction;
	float _damage;
	float _speed;
};

