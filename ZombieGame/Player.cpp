#include "Player.h"

#include <SDL/SDL.h>
#include <iostream>

#include "Gun.h"

Player::Player() : m_currentGunIndex(-1)
{
}

Player::~Player()
{
	for (size_t i = 0; i < p_guns.size(); i++) 
	{
		delete p_guns[i];
	}
}

void Player::init(float speed, glm::vec2 pos)
{
	m_speed = speed;
	m_position = pos;
	m_health = 150;

	m_colour = {/*r*/ 255, /*g*/ 255, /*b*/ 0, /*a*/ 255 };
}

void Player::addGun(Gun* gun)
{
	//Add gun to inventory
	p_guns.push_back(gun);

	if (m_currentGunIndex == -1)
	{
		m_currentGunIndex = 0;
	}
}

void Player::move(float adjustedDeltaTicks, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, std::vector<Bullet>& bullets)
{
	if (m_direction.x != 0 || m_direction.y != 0)
	{
		m_direction = glm::normalize(m_direction);
	}

	m_position += m_direction * m_speed * adjustedDeltaTicks;
	m_direction = { 0, 0 };

	//Guns, aiming, shooting, reloading
	if (m_currentGunIndex != -1)
	{
		// get to coords (top left 0,0) from input manager, use the camera to convert the mouse coords into s2w mouse coords

		glm::vec2 screenToWorldMouseCords = p_cam->screenToWorld(m_mouseCoords); 
		glm::vec2 centrePosition = m_position + glm::vec2(AGENT_RADIUS);

		glm::vec2 direction = glm::normalize(screenToWorldMouseCords - centrePosition);

		p_guns[m_currentGunIndex]->update(adjustedDeltaTicks, m_isMouseDown, centrePosition, direction, bullets);

		for (size_t i = 0; i < p_guns.size(); i++)
		{
			p_guns[i]->reload();
		}
	}
}