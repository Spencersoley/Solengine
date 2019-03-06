#pragma once

#include <Solengine/GLSLProgram.h>
#include <Solengine/Camera2D.h>
#include <Solengine/SpriteBatch.h>
#include <Solengine/Window.h>

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

#include "Level.h"
#include "Bullet.h"
#include "Player.h"

class Zombie;
class Human;

class View
{
public:
	View();
	~View();

	void drawGame();

	void init(std::vector<Level*>* levels, std::vector<Human*>* humans, std::vector<Zombie*>* zombies, std::vector<Bullet>* bullets, Player* player, float screenwidth, float screenheight);

	void update(glm::vec2 playerPos);

	void scale(float scaleSpeed);

	Solengine::Camera2D _SOL_cam;
	Solengine::Window _SOL_window;
	Solengine::SpriteBatch _SOL_agentSpriteBatch;

private: 

	Solengine::GLSLProgram _SOL_shaderProgram;
	
	std::vector<Level*>* _levels;
	std::vector<Human*>* _humans;
	std::vector<Zombie*>* _zombies;
	std::vector<Bullet>* _bullets;

	Player* _player;

	int _currentLevel;

};

