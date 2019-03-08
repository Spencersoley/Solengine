#include "Bullet.h"

#include <iostream>

#include <Solengine/ResourceManager.h>

#include "Agent.h"
#include "Human.h"	
#include "Zombie.h"
#include "Level.h"

//Since these're relatively small in memory, it's better to not store these in a vector of pointers
//This way our data will be contiguous in memory, giving better cache coherency

Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float damage, float speed) :
	m_position(pos),
	m_direction(dir),
	m_damage(damage),
	m_speed(speed)
{
}

Bullet::~Bullet()
{
}

void Bullet::move(float adjustedDeltaTicks)
{
	m_position += m_direction * m_speed * adjustedDeltaTicks;
}

//returns true on collision
bool Bullet::collisionWithAgent(Agent* agent)
{
	const float MIN_DISTANCE = AGENT_RADIUS + BULLET_RADIUS;

	glm::vec2 centrePosA = m_position;
	glm::vec2 centrePosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = centrePosA - centrePosB;

	float dist = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - dist;

	if (collisionDepth > 0)
	{
		return true;
	}

	return false;
}

//returns true on collision
bool Bullet::collisionWithWorld(const std::vector<std::string>& levelData)
{
	glm::ivec2 gridPosition;
	gridPosition.x = (int)floor(m_position.x / (float)TILE_WIDTH);
	gridPosition.y = (int)floor(m_position.y / (float)TILE_WIDTH);

	if (gridPosition.x < 0 || gridPosition.x >= (int)levelData[0].length() ||
		gridPosition.y < 0 || gridPosition.y >= (int)levelData.size())
	{
		return true;
	}

	return (levelData[gridPosition.y][gridPosition.x] != '.');
}

void Bullet::draw(Solengine::SpriteBatch& spriteBatch)
{
	//Our resourcemanager should not be static! change it

	static int textureID = Solengine::ResourceManager::getTexture("Textures/zombie_pack/circle2.png").textureID;

	glm::vec4 destRect(m_position.x + BULLET_RADIUS, m_position.y + BULLET_RADIUS, BULLET_RADIUS * 2, BULLET_RADIUS * 2);
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	Solengine::ColourRGBA8 colour = {/*r*/ 150, /*g*/ 150, /*b*/ 150, /*a*/ 255 };

	spriteBatch.draw(destRect, uvRect, textureID, 0.0f, colour);
}