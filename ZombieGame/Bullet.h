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
	bool collisionWithAgent(Agent* agent); //true on collision?
	bool collisionWithWorld(const std::vector<std::string>& levelData); //true on collision?
	void move(float deltaTime);

	float getDamage() const { return m_damage; }

private:	
	int m_id; //use?
	int m_lifeTime; //use?
	glm::vec2 m_position;
	glm::vec2 m_direction;
	float m_damage;
	float m_speed;
};

