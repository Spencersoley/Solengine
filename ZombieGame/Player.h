#pragma once

#include "Human.h"

#include <Solengine/InputManager.h>
#include <Solengine/Camera2D.h>

#include "Bullet.h"

//#include "Gun.h"
class Gun;

class Player : public Human
{
public:
	Player();
	~Player();

	void init(float speed, glm::vec2 pos, std::vector<Bullet>* bullets);

	void initInputManager(Solengine::InputManager* inputManager);

	void setCamera(Solengine::Camera2D* cam) { _cam = cam; }

	void addGun(Gun* gun);

	void move(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime);

private:
	Solengine::InputManager* _inputManager;

	std::vector<Gun*> _guns;
	int _currentGunIndex;

	Solengine::Camera2D* _cam;
	std::vector<Bullet>* _bullets;
};

