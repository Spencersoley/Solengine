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

	void initShaders();
	void drawGame(std::vector<Level*> levels, std::vector<Human*> humans, std::vector<Zombie*> zombies, std::vector<Bullet> bullets);
	Solengine::Camera2D _SOL_cam;
	Solengine::Window _SOL_window;
	Solengine::SpriteBatch _SOL_agentSpriteBatch;

private: 

	Solengine::GLSLProgram _SOL_shaderProgram;
	
	std::vector<Level*> _levels;
	std::vector<Human*> _humans;
	std::vector<Zombie*> _zombies;

	int _currentLevel;

};

