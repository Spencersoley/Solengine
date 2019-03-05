#include "Human.h"
#include "Zombie.h"

#include <iostream>
#include <random>
#include <ctime>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

//Make humans run from nearest zombie

Human::Human() : _frameCount(0)
{
}

Human::~Human()
{
}

void Human::init(float speed, glm::vec2 pos)
{
	_health = 20.0f;

	static std::mt19937 randomEngine((unsigned int)time(nullptr));
	static std::uniform_real_distribution<float> randomDir(-1.0f, 1.0f);
	std::uniform_int_distribution<int> randomTurnRate(250, 450);

	_turnRate = randomTurnRate(randomEngine);
	

	_colour = {/*r*/ 200, /*g*/ 0, /*b*/ 200, /*a*/ 255 };

	_speed = speed;
	_position = pos;
	_direction = glm::vec2(randomDir(randomEngine), randomDir(randomEngine));
	if (_direction.length() == 0) _direction = glm::vec2(1.0f, 0.0f);
	_direction = glm::normalize(_direction);
}

void Human::move(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime)
{
	_frameCount;
	_frameCount++;

	//Scan for nearest zombie
	if (_frameCount%10 == 0)
	{
		_nearestZombie = getNearestZombie(zombies);
	}

	//Movement depends on whether a _nearestZombie is recognised
	if (_nearestZombie == nullptr)
	{	
		//Automatic random turning based on fixed rate
		if (_frameCount > _turnRate)
		{
			redirect();
			//std::cout << "redirect" << frameCount << std::endl;
			_frameCount = 0;
			
		}
	}
	else
	{
		//Run away from _nearestZombie
		_direction = glm::normalize(_position - _nearestZombie->getPosition());
	}

	//Come up with a better algorithm for breaking up human movement
	const int _turnPause = 500 - _turnRate;

	if (_frameCount > _turnPause)
	{
		_position += _direction * _speed * deltaTime;
	}
}

Zombie* Human::getNearestZombie(std::vector<Zombie*>& zombies)
{
	Zombie* nearestZombie = nullptr;

	float smallestDistance = 250.0f;

	for (size_t i = 0; i < zombies.size(); i++)
	{
		glm::vec2 distVec = zombies[i]->getPosition() - _position;
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

	_direction = glm::rotate(_direction, glm::radians(randRotate(randomEngine)));
}
