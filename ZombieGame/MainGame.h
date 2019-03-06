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
	void processInput();
	void updatePhysics(float totalDeltaTime, float MAX_PHYSICS_STEPS, float MAX_DELTA_TIME);

	void updateAgents(float deltaTime);
	void updateBullets(float deltaTime);


	int m_screenWidth;
	int m_screenHeight;
	Solengine::GameState m_gameState;
	bool m_announceInConsoleFPS;
	int m_currentLevel;

	//SOL helps indicate engine use
	Solengine::FPSManager m_SOL_fpsManager;

	View m_view;
	Controller m_controller;
	Player m_player;

	std::vector<Bullet> mm_bullets;
	std::vector<Level*> mp_levels;
	std::vector<Human*> mp_humans;
	std::vector<Zombie*> mp_zombies;		

	int m_fpsMax;

	int m_numHumansKilled;
	int m_numZombiesKilled;


	Uint32 m_frameTime;
};

