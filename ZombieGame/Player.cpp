#include "Player.h"

#include <SDL/SDL.h>
#include <iostream>

#include "Gun.h"


Player::Player() : m_currentGunIndex(-1)
{
}

Player::~Player()
{
	for (size_t i = 0; i < p_guns.size(); i++) {
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

void Player::initInputManager(Solengine::InputManager* inputManager)
{
	p_inputManager = inputManager;
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

void Player::move(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, std::vector<Bullet>& bullets, float adjustedDeltaTicks)
{
	glm::vec2 direction = { 0, 0 };

	if (p_inputManager->keyState(SDLK_w))
	{
		direction.y += 1;
	}

	if (p_inputManager->keyState(SDLK_s))
	{
		direction.y -= 1;
	}

	if (p_inputManager->keyState(SDLK_a))
	{
		direction.x -= 1;
	}

	if (p_inputManager->keyState(SDLK_d))
	{
		direction.x += 1;
	}

	if (p_inputManager->keyState(SDLK_1) && p_guns.size() >= 0)
	{
		m_currentGunIndex = 0;
	}

	if (p_inputManager->keyState(SDLK_2) && p_guns.size() >= 1)
	{
		m_currentGunIndex = 1;
	}

	if (p_inputManager->keyState(SDLK_3) && p_guns.size() >= 2)
	{
		m_currentGunIndex = 2;
	}

	if (direction.x != 0 || direction.y != 0)
	{
		direction = glm::normalize(direction);
	}

	m_position += direction * m_speed * adjustedDeltaTicks;

	//Guns, aiming, shooting, reloading
	if (m_currentGunIndex != -1)
	{
		glm::vec2 mouseCoords = p_inputManager->getMouseCoords();
		mouseCoords = p_cam->screenToWorld(mouseCoords);

		glm::vec2 centrePosition = m_position + glm::vec2(AGENT_RADIUS);

		glm::vec2 direction = glm::normalize(mouseCoords - centrePosition);

		p_guns[m_currentGunIndex]->update(p_inputManager->keyState(SDL_BUTTON_LEFT),
			centrePosition,
			direction,
			bullets,
			adjustedDeltaTicks);

		for (size_t i = 0; i < p_guns.size(); i++)
		{
			p_guns[i]->reload();
		}
	}
}