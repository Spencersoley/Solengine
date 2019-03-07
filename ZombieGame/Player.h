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
	void initInputManager(Solengine::InputManager* inputManager); //best way to handle the reference?
	void setCamera(Solengine::Camera2D* cam) { p_cam = cam; }
	void addGun(Gun* gun);
	void move(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, std::vector<Bullet>& bullets, float deltaTime); //Why can we override this but not zombie/human's move

private:
	std::vector<Gun*> p_guns;
	Solengine::InputManager* p_inputManager;
	Solengine::Camera2D* p_cam;	

	int m_currentGunIndex;
};

