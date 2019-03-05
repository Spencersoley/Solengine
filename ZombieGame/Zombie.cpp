#include "Zombie.h"

#include "Human.h"

Zombie::Zombie() : _frames(0)
{
}

Zombie::~Zombie()
{
}

void Zombie::init(float speed, glm::vec2 pos)
{
	_health = 150;
	_speed = speed;
	_position = pos;

	_colour = {/*r*/ 0, /*g*/ 150, /*b*/ 0, /*a*/ 255 };
}

void Zombie::move(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime)
{
	// Find the closest human every 80 frames
	if (_frames > 80 || _nearestHuman == nullptr)
	{
		_nearestHuman = getNearestHuman(humans);
		_frames = 0;
	}
	
	// If we found a human, move towards him
	if (_nearestHuman != nullptr) {
		// Get the direction vector twoards the player
		_direction = glm::normalize(_nearestHuman->getPosition() - _position);
		_position += _direction * _speed * deltaTime;
	}

	_frames++;
}

Human* Zombie::getNearestHuman(std::vector<Human*>& humans) 
{
	Human* nearestHuman = nullptr;

	float smallestDistance = 50000.0f;

	for (size_t i = 0; i < humans.size(); i++)
	{
		glm::vec2 distVec = humans[i]->getPosition() - _position;
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