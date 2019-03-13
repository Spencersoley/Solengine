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

	void init(Player* player, Solengine::Camera2D* cam, int screenwidth, int screenheight);
	void update(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, std::vector<Level*>& levels, std::vector<Bullet>& m_bullets);

private: 
	void drawGame(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, std::vector<Level*>& levels, std::vector<Bullet>& bullets);

	void drawHumans(std::vector<Human*>& humans);
	void drawZombies(std::vector<Zombie*>& zombies);
	void drawBullets(std::vector<Bullet>& bullets);

	Solengine::GLSLProgram m_SOL_shaderProgram;
	Solengine::Window m_SOL_window;
	Solengine::SpriteBatch m_SOL_agentSpriteBatch;

	Solengine::Camera2D* p_SOL_cam = nullptr;
	Player* p_player = nullptr;
	int m_currentLevel;
};

