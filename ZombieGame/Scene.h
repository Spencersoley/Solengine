#pragma once

#include <Solengine/SDLInitialiser.h>
#include <Solengine/ErrorHandler.h>
#include <Solengine/GLSLProgram.h>
#include <Solengine/GLTexture.h>
#include <Solengine/Window.h>
#include <Solengine/FPSManager.h>
#include <Solengine/Camera2D.h>
#include <Solengine/SpriteBatch.h>
#include <Solengine/InputManager.h>
#include <Solengine/GameState.h>

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>

#include "Bullet.h"
#include "Level.h"
#include "Player.h"
#include "Model.h"
#include "View.h"
#include "Controller.h"

class Zombie;

class Scene
{
public:
	Scene();
	~Scene();

	void run();

private:
	void initSystems();
	void initLevel();
	void gameLoop();
	void checkVictory();

	Solengine::FPSManager m_SOL_fpsManager;
	Solengine::Camera2D m_SOL_cam;
	Solengine::Camera2D m_SOL_uiCam;
	Model m_model;
	View m_view;
	Controller m_controller;
	Player m_player;



	std::vector<Bullet> m_bullets;
	std::vector<Level*> p_levels;
	std::vector<Human*> p_humans;
	std::vector<Zombie*> p_zombies;

	std::vector<std::vector<Node>> m_defaultNodeField;

	Solengine::GameState m_gameState;
	int m_screenWidth;
	int m_screenHeight;
	int m_currentLevel;	
	int m_fpsMax;
	float m_gameSpeed; // (0.02 is slow, 0.1 is fast)
	int m_numHumansKilled;
	int m_numZombiesKilled;
	Uint32 m_frameTime;
	bool m_announceFPS; //rename this	
};

