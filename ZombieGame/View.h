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

	void init(Player* player, float screenwidth, float screenheight);
	void update(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, std::vector<Level*>& levels, std::vector<Bullet>& mm_bullets);
	void scale(float scaleSpeed);

private: 
	void drawGame(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, std::vector<Level*>& levels, std::vector<Bullet>& bullets);

	Solengine::GLSLProgram m_SOL_shaderProgram;
	Solengine::Camera2D m_SOL_cam;
	Solengine::Window m_SOL_window;
	Solengine::SpriteBatch m_SOL_agentSpriteBatch;
	Player* p_player;
	int _currentLevel;

};

