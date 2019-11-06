#pragma once

#include <Solengine/GLSLProgram.h>
#include <Solengine/ICamera.h>
#include <Solengine/SpriteBatch.h>
#include <Solengine/Window.h>
#include <Solengine/Font.h>

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

	void init(Player* player, Solengine::ICamera* cam, Solengine::ICamera* uiCam, int screenwidth, int screenheight);
	void update(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, std::vector<Level*>& levels, std::vector<Bullet>& m_bullets);

private: 
	void drawGame(std::vector<Human*>& humans, std::vector<Zombie*>& zombies, std::vector<Level*>& levels, std::vector<Bullet>& bullets);

	void drawHumans(std::vector<Human*>& humans);
	void drawZombies(std::vector<Zombie*>& zombies);
	void drawBullets(std::vector<Bullet>& bullets);
	void drawUI(size_t zombiesSize);

	Solengine::GLSLProgram m_SOL_shaderProgram;
	Solengine::Window m_SOL_window;
	Solengine::SpriteBatch m_SOL_agentSpriteBatch;
	Solengine::SpriteBatch m_SOL_uiSpriteBatch;

	Solengine::Font* p_SOL_spriteFont = nullptr;

	Solengine::ICamera* p_SOL_cam = nullptr;
	Solengine::ICamera* p_SOL_uiCam = nullptr;
	Player* p_player = nullptr;

	int m_screenHeight;
	int m_screenWidth;
	int m_currentLevel;
};

