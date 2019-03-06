#include "Human.h"
#include "Zombie.h"

#include <iostream>
#include <random>
#include <ctime>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

//Make humans run from nearest zombie

Human::Human() : m_frameCount(0)
{
}

Human::~Human()
{
}

void Human::init(float speed, glm::vec2 pos)
{
	m_health = 20.0f;

	static std::mt19937 randomEngine((unsigned int)time(nullptr));
	static std::uniform_real_distribution<float> randomDir(-1.0f, 1.0f);
	std::uniform_int_distribution<int> randomTurnRate(250, 450);

	m_turnRate = randomTurnRate(randomEngine);	

	m_colour = {/*r*/ 200, /*g*/ 0, /*b*/ 200, /*a*/ 255 };

	m_speed = speed;
	m_position = pos;
	m_direction = glm::vec2(randomDir(randomEngine), randomDir(randomEngine));
	if (m_direction.length() == 0) m_direction = glm::vec2(1.0f, 0.0f);
	m_direction = glm::normalize(m_direction);
}

void Human::move(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime)
{
	m_frameCount;
	m_frameCount++;

	//Scan for nearest zombie
	if (m_frameCount%10 == 0)
	{
		p_nearestZombie = getNearestZombie(zombies);
	}

	//Movement depends on whether a _nearestZombie is recognised
	if (p_nearestZombie == nullptr)
	{	
		//Automatic random turning based on fixed rate
		if (m_frameCount > m_turnRate)
		{
			redirect();
			//std::cout << "redirect" << frameCount << std::endl;
			m_frameCount = 0;		
		}
	}
	else
	{
		//Run away from _nearestZombie
		m_direction = glm::normalize(m_position - p_nearestZombie->getPosition());
	}

	//Come up with a better algorithm for breaking up human movement
	const int _turnPause = 500 - m_turnRate;

	if (m_frameCount > _turnPause)
	{
		m_position += m_direction * m_speed * deltaTime;
	}
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
