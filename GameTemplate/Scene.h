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

