#include "Zombie.h"

#include "Human.h"

Zombie::Zombie() 
{
}

Zombie::~Zombie()
{
}

void Zombie::init(float speed, glm::vec2 pos, std::vector<std::vector<Node>> nodeField)
{
	m_health = 150;
	m_speed = speed;
	m_position = pos;
	m_colour = {/*r*/ 0, /*g*/ 150, /*b*/ 0, /*a*/ 255 };
	m_pathfinder.setNodeField(nodeField);
	m_pathfinder.setTileWidth(TILE_WIDTH);
}

void Zombie::move(float adjustedDeltaTicks, int globalFrameCount, std::vector<Human*>& humans, std::vector<Zombie*>& zombies)
{
	static int frameCount;
	frameCount++;
	// Find the closest human every 120 
	if (frameCount%120 || p_nearestHuman == nullptr)
	{
		p_nearestHuman = getNearestHuman(humans);
		frameCount = 0;
	}
	
	// If we found a human, move towards them
	if (p_nearestHuman != nullptr) 
	{
		float chaseDistance = 150.0f;

		glm::vec2 distVec = p_nearestHuman->getPosition() - m_position;
		float distance = glm::length(distVec);

		if (distance < chaseDistance)
		{
			m_direction = glm::normalize(p_nearestHuman->getPosition() - m_position);
		} 
		else
		{		
			m_pathfinder.pathfind(m_position, p_nearestHuman->getPosition());
			m_direction = m_pathfinder.getDirectionToNextNode(m_position);
		}

		//what if we only got direction to next node once we're fully within the node?

		m_position += m_direction * m_speed * adjustedDeltaTicks;
	}
}

Human* Zombie::getNearestHuman(std::vector<Human*>& humans) 
{
	Human* nearestHuman = nullptr;

	float smallestDistance = 50000.0f;

	for (size_t i = 0; i < humans.size(); i++)
	{
		glm::vec2 distVec = humans[i]->getPosition() - m_position;
		float distance = glm::length(distVec);

		if (distance < smallestDistance)
		{
			smallestDistance = distance;
			nearestHuman = humans[i];
		}
	}

	return nearestHuman;
}

void Zombie::redirect()
{

}