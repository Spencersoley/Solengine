#include "Scene.h"

#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>

#include <Solengine/ResourceManager.h>
#include <Solengine/SDLInitialiser.h>
#include <Solengine/ErrorHandler.h>

//Constructor will initialise private member variables
Scene::Scene() :
	m_screenWidth(1200),
	m_screenHeight(600),
	m_gameState(Solengine::GameState::PLAY),
	m_currentLevel(0),
	m_fpsMax(60),
	m_physicsSpeed(0.02f),
	m_announceFPS(true)
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
	
	m_model.init(m_physicsSpeed);
	m_view.init(&m_SOL_cam, &m_SOL_uiCam, m_screenWidth, m_screenHeight);
	m_controller.init(&m_SOL_cam);

	initScene();
}

//Initialise the game content
void Scene::initScene()
{
	//Make sure we draw the level --> VIEW
	p_levels.push_back(new Level(m_SOL_tileLevelLoader.ParseLevelData("Levels/DQlevel1.txt")));
}

//Game loop
void Scene::gameLoop()
{
	const float DESIRED_TICKS_PER_FRAME = 1000 / (float)m_fpsMax;
	static int pauseDuration = 0;
	//When initialised to true, this enables fps console announcing
	bool trackFPS = m_announceFPS;

	while (m_gameState != Solengine::GameState::EXIT)
	{
		while (m_gameState == Solengine::GameState::PLAY)
		{

			m_model.update(pauseDuration);

			//handles rendering
			m_view.update(p_levels);

			//handles input
			m_gameState = m_controller.playStateInput();

			//Calculates, announces, and limits FPS
			m_SOL_fpsManager.limitFPS(trackFPS, (int)DESIRED_TICKS_PER_FRAME);

			pauseDuration = 0;
		}

		int pauseClockStart = SDL_GetTicks();
		while (m_gameState == Solengine::GameState::PAUSE)
		{

		}
		pauseDuration = SDL_GetTicks() - pauseClockStart;
	}
}

