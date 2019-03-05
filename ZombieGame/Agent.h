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

	virtual void move(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime) = 0;

	void collisionWithLevel(const std::vector<std::string>& levelData);

	bool collisionWithAgent(Agent* agent);

	//true on death
	bool applyDamage(float damage);

	void draw(Solengine::SpriteBatch& _spriteBatch);

	//Do we have a real reason to use a getter? Is const for access without modification?
	glm::vec2 getPosition() const { return _position; }

protected:

	void checkTilePosition(const std::vector<std::string>& levelData,
		                   std::vector<glm::vec2>& collideTilePositions,                  
	                       float x, float y);

	void collisionWithTile(glm::vec2 tilePos);

	virtual void redirect() = 0;

	glm::vec2 _position;
	glm::vec2 _direction;

	float _speed;
	float _health;

	Solengine::ColourRGBA8 _colour;
};

