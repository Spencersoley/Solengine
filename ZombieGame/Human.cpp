#include "Human.h"
#include "Zombie.h"

#include <iostream>
#include <random>
#include <ctime>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

Human::Human()
{
}

Human::~Human()
{
}

void Human::init(float speed, glm::vec2 pos, int id)
{
	_id = id;

	m_health = 20.0f;

	static std::mt19937 randomEngine((unsigned int)time(nullptr));
	static std::uniform_real_distribution<float> randomDir(-1.0f, 1.0f);
	std::uniform_int_distribution<int> randomTurnRate(120, 240);

	m_turnRate = randomTurnRate(randomEngine);	

	m_colour = {/*r*/ 200, /*g*/ 0, /*b*/ 200, /*a*/ 255 };

	m_speed = speed;
	m_position = pos;
	m_direction = glm::vec2(randomDir(randomEngine), randomDir(randomEngine));
	if (m_direction.length() == 0) m_direction = glm::vec2(1.0f, 0.0f);
	m_direction = glm::normalize(m_direction);
}

void Human::move(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime, int globalFrameCount)
{
	//Scan for nearest zombie, EACH human calls frameCount++, so it might not ever be %60==0 on their turn
	if (globalFrameCount%60 == 0)
	{
		p_nearestZombie = getNearestZombie(zombies);

		if (p_nearestZombie != nullptr)
		{
			m_colour = {/*r*/ 200, /*g*/ 0, /*b*/ 0, /*a*/ 255 };
		}
		else
		{
			m_colour = {/*r*/ 200, /*g*/ 0, /*b*/ 200, /*a*/ 255 };
		}
	}

	//Movement depends on whether a _nearestZombie is recognised
	if (p_nearestZombie == nullptr)
	{	
		//Automatic random turning based on fixed rate
		if (globalFrameCount%m_turnRate == 0)
		{		
			redirect();
		}
	}
	else
	{
		//Run away from _nearestZombie
		m_direction = glm::normalize(m_position - p_nearestZombie->getPosition());
	}

	m_position += m_direction * m_speed * deltaTime;
}

Zombie* Human::getNearestZombie(std::vector<Zombie*>& zombies)
{
	Zombie* nearestZombie = nullptr;

	float smallestDistance = 250.0f;

	for (size_t i = 0; i < zombies.size(); i++)
	{
		glm::vec2 distVec = zombies[i]->getPosition() - m_position;
		float distance = glm::length(distVec);

		if (distance < smallestDistance)
		{
			smallestDistance = distance;
			nearestZombie = zombies[i];
		}
	}

    return nearestZombie;
}

void Human::redirect()
{
	std::mt19937 randomEngine((unsigned int)time(nullptr));
	std::uniform_real_distribution<float> randRotate(60.0f, 300.0f);

	m_direction = glm::rotate(m_direction, glm::radians(randRotate(randomEngine)));
}
