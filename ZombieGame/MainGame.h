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
#include "View.h"
#include "Controller.h"

class Zombie;

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	void initSystems();
	void initLevel();
	void gameLoop();
	std::tuple<float, float> getDeltaTimeAndTotalTicks(float desiredFrametime, float prevTicks);
	void checkVictory();
	void updatePhysics(float totalDeltaTime, float MAX_PHYSICS_STEPS, float MAX_DELTA_TIME);
	void updateAgents(float deltaTime);
	void updateBullets(float deltaTime);

	Solengine::GameState m_gameState;
	int m_screenWidth;
	int m_screenHeight;
	int m_currentLevel;
	bool m_announceInConsoleFPS;
	int m_fpsMax;
	int m_numHumansKilled;
	int m_numZombiesKilled;
	Uint32 m_frameTime;

	Solengine::FPSManager m_SOL_fpsManager;
	View m_view;
	Controller m_controller;
	Player m_player;

	std::vector<Bullet> m_bullets;
	std::vector<Level*> p_levels;
	std::vector<Human*> p_humans;
	std::vector<Zombie*> p_zombies;		
};

