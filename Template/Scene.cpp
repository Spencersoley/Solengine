#include "Scene.h"

#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>

#include <Solengine/ResourceManager.h>
#include <Solengine/SDLInitialiser.h>
#include <Solengine/ErrorHandler.h>

//Move random engine to Solengine?
//init vs constructors?
//fix 'stats' numhumanskilled etc
//Goal-Based pathfinding

//NTS: It's okay to have global variables if they're constant
const float HUMAN_SPEED = 1.0f;
const float ZOMBIE_SPEED = 2.0f;
const float PLAYER_SPEED = 10.0f;

//Constructor will initialise private member variables
Scene::Scene() :
	m_screenWidth(1200),
	m_screenHeight(600),
	m_gameState(Solengine::GameState::PLAY),
	m_currentLevel(0),
	m_fpsMax(60),
	m_gameSpeed(0.02f),
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
	//initSystems();
	//gameLoop();
}

//Initialise SDL, glew, OpenGL, shaders, fps manager and level
void Scene::initSystems()
{

}

//Initialise the game content
void Scene::initLevel()
{

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
			m_view.update();

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

