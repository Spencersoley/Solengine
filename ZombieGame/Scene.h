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
	Uint32 getDeltaTicks();
	void updatePhysics(float MAX_PHYSICS_STEPS, float MAX_DELTA_TIME, int pauseDuration);
	void updateAgents(float adjustedDeltaTicks);
	void updateBullets(float adjustedDeltaTicks);

	Solengine::FPSManager m_SOL_fpsManager;
	Solengine::Camera2D m_SOL_cam;
	View m_view;
	Controller m_controller;
	Player m_player;

	std::vector<Bullet> m_bullets;
	std::vector<Level*> p_levels;
	std::vector<Human*> p_humans;
	std::vector<Zombie*> p_zombies;

	Solengine::GameState m_gameState;
	int m_screenWidth;
	int m_screenHeight;
	int m_currentLevel;	
	int m_fpsMax;
	float m_gameSpeed; // (0.02 is slow, 0.1 is fast)
	int m_numHumansKilled;
	int m_numZombiesKilled;
	int m_globalFrameCount;
	Uint32 m_frameTime;
	bool m_announceInConsoleFPS; //rename this	
};

