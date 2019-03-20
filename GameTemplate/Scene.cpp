#include "Scene.h"

#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>

#include <Solengine/ResourceManager.h>
#include <Solengine/SDLInitialiser.h>
#include <Solengine/ErrorHandler.h>


Scene::Scene() :
	m_screenWidth(1200),
	m_screenHeight(600),
	m_gameState(Solengine::GameState::PLAY),
	m_currentLevel(0),
	m_fpsMax(60),
	m_gameSpeed(0.02f),
	m_announceInConsoleFPS(true),
	m_numHumansKilled(0),
	m_numZombiesKilled(0),
	m_globalFrameCount(0)
{

}

//Destructor
Scene::~Scene()
{

}

//Runs the game
void Scene::run()
{
	initSystems();
	gameLoop();
}

//Initialise SDL, glew, OpenGL, shaders, fps manager and level
void Scene::initSystems()
{
	Solengine::initialiseSDL();
	/*m_model.init(&m_player, m_currentLevel, m_gameSpeed);
	m_view.init(&m_player, &m_SOL_cam, &m_SOL_uiCam, m_screenWidth, m_screenHeight);
	initLevel();
	m_controller.init(&m_SOL_cam, &m_player, p_levels);*/
}

//Initialise the game content
void Scene::initLevel()
{
	/*
	std::mt19937 randomEngine;
	randomEngine.seed((unsigned int)time(nullptr));
	std::uniform_int_distribution<int> randX(2, p_levels[m_currentLevel]->getWidth() - 2);
	std::uniform_int_distribution<int> randY(2, p_levels[m_currentLevel]->getHeight() - 2);
	*/
}

//Game loop
void Scene::gameLoop()
{
	const float DESIRED_TICKS_PER_FRAME = 1000 / (float)m_fpsMax;
	static int pauseDuration = 0;
	//When initialised to true, this enables fps console announcing
	bool trackFPS = m_announceInConsoleFPS;

	while (m_gameState != Solengine::GameState::EXIT)
	{
		/*
		while (m_gameState == Solengine::GameState::PLAY)
		{
			m_model.updateModel(pauseDuration, p_humans, p_zombies, p_levels, m_bullets);

			//handles rendering
			m_view.update(p_humans, p_zombies, p_levels, m_bullets);

			//handles input
			m_gameState = m_controller.playStateInput();

			//Calculates, announces, and limits FPS
			m_SOL_fpsManager.limitFPS(trackFPS, (int)DESIRED_TICKS_PER_FRAME);

			pauseDuration = 0;
		}

		int pauseClockStart = SDL_GetTicks();
		while (m_gameState == Solengine::GameState::PAUSE)
		{
			m_gameState = m_controller.pauseStateInput();

			m_SOL_fpsManager.limitFPS(trackFPS, (int)DESIRED_TICKS_PER_FRAME);
		}
		pauseDuration = SDL_GetTicks() - pauseClockStart;
		*/
	}
}


