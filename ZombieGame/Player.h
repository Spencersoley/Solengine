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

	void init(float speed, glm::vec2 pos);

	void initInputManager(Solengine::InputManager* inputManager);

	void setCamera(Solengine::Camera2D* cam) { p_cam = cam; }

	void addGun(Gun* gun);

	void move(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, std::vector<Bullet>& bullets, float deltaTime);

private:
	int m_currentGunIndex;
	std::vector<Gun*> mp_guns;


	Solengine::InputManager* p_inputManager;
	Solengine::Camera2D* p_cam;	
};

