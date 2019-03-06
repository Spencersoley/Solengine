#include "Player.h"

#include <SDL/SDL.h>
#include <iostream>

#include "Gun.h"


Player::Player() : m_currentGunIndex(-1)
{
}

Player::~Player()
{
	for (size_t i = 0; i < mp_guns.size(); i++) {
		delete mp_guns[i];
	}
}

void Player::init(float speed, glm::vec2 pos, std::vector<Bullet>* bullets)
{
	m_bullets = bullets;
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
	mp_guns.push_back(gun);

	if (m_currentGunIndex == -1)
	{
		m_currentGunIndex = 0;
	}
}

void Player::move(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime)
{
	glm::vec2 direction = { 0, 0 };

	if (p_inputManager->key(SDLK_w))
	{
		direction.y += 1;
	}

	if (p_inputManager->key(SDLK_s))
	{
		direction.y -= 1;
	}

	if (p_inputManager->key(SDLK_a))
	{
		direction.x -= 1;
	}

	if (p_inputManager->key(SDLK_d))
	{
		direction.x += 1;
	}

	if (p_inputManager->key(SDLK_1) && mp_guns.size() >= 0)
	{
		m_currentGunIndex = 0;
	}

	if (p_inputManager->key(SDLK_2) && mp_guns.size() >= 1)
	{
		m_currentGunIndex = 1;
	}

	if (p_inputManager->key(SDLK_3) && mp_guns.size() >= 2)
	{
		m_currentGunIndex = 2;
	}

	if (direction.x != 0 || direction.y != 0)
	{
		direction = glm::normalize(direction);
	}

	m_position += direction * m_speed * deltaTime;

	//Guns, aiming, shooting, reloading
	if (m_currentGunIndex != -1)
	{
		glm::vec2 mouseCoords = p_inputManager->getMouseCoords();
		mouseCoords = p_cam->screenToWorld(mouseCoords);

		glm::vec2 centrePosition = m_position + glm::vec2(AGENT_RADIUS);

		glm::vec2 direction = glm::normalize(mouseCoords - centrePosition);

		mp_guns[m_currentGunIndex]->update(p_inputManager->key(SDL_BUTTON_LEFT),
			centrePosition,
			direction,
			*m_bullets,
			deltaTime);

		for (size_t i = 0; i < mp_guns.size(); i++)
		{
			mp_guns[i]->reload();
		}
	}
}