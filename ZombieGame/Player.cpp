#include "Player.h"

#include <SDL/SDL.h>

#include "Gun.h"

Player::Player() : _currentGunIndex(-1)
{
}

Player::~Player()
{
	for (size_t i = 0; i < _guns.size(); i++) {
		delete _guns[i];
	}
}


//init vs constructor?
void Player::init(float speed, glm::vec2 pos, Solengine::InputManager* inputManager, Solengine::Camera2D* cam, std::vector<Bullet>* bullets)
{
	_bullets = bullets;
	_inputManager = inputManager;
	_cam = cam;
	_speed = speed;
	_position = pos;
	_health = 150;

	_colour = {/*r*/ 255, /*g*/ 255, /*b*/ 0, /*a*/ 255 };
}

void Player::addGun(Gun* gun)
{
	//Add gun to inventory
	_guns.push_back(gun);

	if (_currentGunIndex == -1)
	{
		_currentGunIndex = 0;
	}
}

void Player::move(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime)
{
	if (_inputManager->key(SDLK_w))
	{
		_position.y += _speed * deltaTime;
	}

	if (_inputManager->key(SDLK_s))
	{
		_position.y -= _speed * deltaTime;
	}

	if (_inputManager->key(SDLK_a))
	{
		_position.x -= _speed * deltaTime;
	}

	if (_inputManager->key(SDLK_d))
	{
		_position.x += _speed * deltaTime;
	}

	if (_inputManager->key(SDLK_1) && _guns.size() >= 0)
	{
		_currentGunIndex = 0;
	}

	if (_inputManager->key(SDLK_2) && _guns.size() >= 1)
	{
		_currentGunIndex = 1;
	}

	if (_inputManager->key(SDLK_3) && _guns.size() >= 2)
	{
		_currentGunIndex = 2;
	}

	//Guns, aiming, shooting, reloading
	if (_currentGunIndex != -1)
	{
		glm::vec2 mouseCoords = _inputManager->getMouseCoords();
		mouseCoords = _cam->screenToWorld(mouseCoords);

		glm::vec2 centrePosition = _position + glm::vec2(AGENT_RADIUS);

		glm::vec2 direction = glm::normalize(mouseCoords - centrePosition);

		_guns[_currentGunIndex]->update(_inputManager->key(SDL_BUTTON_LEFT),
			centrePosition,
			direction,
			*_bullets,
			deltaTime);

		for (size_t i = 0; i < _guns.size(); i++)
		{
			_guns[i]->reload();
		}
	}
}