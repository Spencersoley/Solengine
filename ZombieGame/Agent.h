#pragma once

#include <glm/glm.hpp>

#include "Solengine/SpriteBatch.h"
#include "Level.h"

const float AGENT_WIDTH = 40.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

class Zombie;
class Human;

class Agent
{
public:
	Agent();
	virtual ~Agent();

	virtual void move(float adjustedDeltaTicks, int globalFrameCount, std::vector<Human*>& humans, std::vector<Zombie*>& zombies) = 0;

	void collisionWithLevel(const std::vector<std::string>& levelData);
	bool collisionWithAgent(Agent* agent); //true on collision?
	bool applyDamage(float damage); //true on death
	void draw(Solengine::SpriteBatch& _spriteBatch);

	glm::vec2 getPosition() const { return m_position; }

protected:
	void checkTilePosition(const std::vector<std::string>& levelData,
		                   std::vector<glm::vec2>& collideTilePositions,                  
	                       float x, float y);
	void collisionWithTile(glm::vec2 tilePos);
	virtual void redirect() = 0;

	float m_speed;
	float m_health;
	glm::vec2 m_position;
	glm::vec2 m_direction;
	Solengine::ColourRGBA8 m_colour;
};

