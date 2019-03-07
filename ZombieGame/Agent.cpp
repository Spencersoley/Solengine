#include "Agent.h"

#include <algorithm>
#include <iostream>

#include "Solengine/ResourceManager.h"

Agent::Agent()
{
}

Agent::~Agent()
{
}

//Called every frame for every agent
void Agent::collisionWithLevel(const std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collideTilePositions;

	//Adds tiles occupied by the corners of the agent to a vector.
	//Will only add the tile if it's not an empty space.
	checkTilePosition(levelData,
		              collideTilePositions,
		              m_position.x, m_position.y);

	checkTilePosition(levelData,
		              collideTilePositions,
	              	  m_position.x + AGENT_WIDTH, m_position.y);

	checkTilePosition(levelData,
		              collideTilePositions,
		              m_position.x, m_position.y + AGENT_WIDTH);

	checkTilePosition(levelData,
	                  collideTilePositions,
	       	          m_position.x + AGENT_WIDTH , m_position.y + AGENT_WIDTH);

	//Calls a collision function on the tiles in the vector
	for (size_t i = 0; i < collideTilePositions.size(); i++)
	{
		collisionWithTile(collideTilePositions[i]);
	}
}

void Agent::checkTilePosition(const std::vector<std::string>& levelData,
	std::vector<glm::vec2>& collideTilePositions,
	float x, float y)
{
	glm::vec2 cornerPos = glm::vec2(floor(x / (float)TILE_WIDTH),
		floor(y / (float)TILE_WIDTH));

	//return when outside the world
	if (cornerPos.x < 0 || cornerPos.x >= levelData[0].length() ||
		cornerPos.y < 0 || cornerPos.y >= levelData.size())
	{
		return;
	}

	if (levelData[(const unsigned int)cornerPos.y][(const unsigned int)cornerPos.x] != '.')
	{
		collideTilePositions.push_back(cornerPos * (float)TILE_WIDTH  + glm::vec2((float)TILE_WIDTH / 2.0f));
	}
}

//Axis aligned bounty box collision, or AABB: determines distance between centrepoints of agent and tile position
//moving the agent based on their position relative to the tile.
void Agent::collisionWithTile(glm::vec2 tilePos)
{                               
	const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

	//Get a vector of the distance between the colliding tile and the agent
	glm::vec2 centrePos = m_position + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = centrePos - tilePos;
	
	float xDepth = MIN_DISTANCE - abs(distVec.x);
	float yDepth = MIN_DISTANCE - abs(distVec.y);

	// If the minimum collision distance is greater than the current distance, we have a collision
	if (xDepth > 0 && yDepth > 0)
	{
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f))
		{
			if (distVec.x < 0)
			{
				m_position.x -= xDepth;
			}
			else
			{
				m_position.x += xDepth;
			}

			redirect();
		}		
		else if (std::max(xDepth, 0.0f) > std::max(yDepth, 0.0f))
		{
			if (distVec.y < 0)
			{
				m_position.y -= yDepth;
			}
			else
			{
				m_position.y += yDepth;
			}

			redirect();
		}
	}
}

//Circular collision
bool Agent::collisionWithAgent(Agent* agent)
{
	const float MIN_DISTANCE = 2.0f * AGENT_RADIUS;

	glm::vec2 centrePosA = m_position + glm::vec2(AGENT_RADIUS);
	glm::vec2 centrePosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = centrePosA - centrePosB;

	float dist = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - dist;

	if (collisionDepth > 0)
	{
		glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;

		m_position += collisionDepthVec / 2.0f;
		agent->m_position -= collisionDepthVec / 2.0f;
		return true;
	}

	return false;
}

bool Agent::applyDamage(float damage)
{
	m_health -= damage;
	if (m_health <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Agent::draw(Solengine::SpriteBatch& spriteBatch)
{
	//uses Solengine::ResourceManager to grab the textureID, passes it to the spriteBatch.
	static int textureID = Solengine::ResourceManager::getTexture("Textures/zombie_pack/circle.png").textureID;

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = m_position.x;
	destRect.y = m_position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;

	spriteBatch.draw(destRect, uvRect, textureID, 0.0f, m_colour);
}