#include "Scene.h"

#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>

#include <Solengine/ResourceManager.h>
#include <Solengine/SDLInitialiser.h>
#include <Solengine/ErrorHandler.h>

#include "Zombie.h"
#include "Gun.h"

//Move random engine to Solengine?
//init vs constructors?
//fix 'stats' numhumanskilled etc
//Goal-Based pathfinding

//NTS: It's okay to have global variables if they're constant
const float HUMAN_SPEED = 1.0f;
const float ZOMBIE_SPEED = 15.0f;
const float PLAYER_SPEED = 10.0f;

//Constructor will initialise private member variables
Scene::Scene() :
	m_screenWidth(1200),
	m_screenHeight(600),
	m_gameState(Solengine::GameState::PLAY),
	m_currentLevel(0),
	m_fpsMax(600),
	m_gameSpeed(0.02f),
	m_announceInConsoleFPS(false),
	m_numHumansKilled(0),
	m_numZombiesKilled(0),
	m_globalFrameCount(0)
{

}

//Destructor
Scene::~Scene()
{
	for (size_t i = 0; i < p_levels.size(); i++)
	{
		delete p_levels[i];
	}
	for (size_t i = 1; i < p_humans.size(); i++) 
	{
		delete p_humans[i];
	}
	for (size_t i = 0; i < p_zombies.size(); i++) 
	{
		delete p_zombies[i];
	}
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
	m_model.init(&m_player, m_currentLevel, m_gameSpeed, &m_pathfinder);
	m_view.init(&m_player, &m_SOL_cam, m_screenWidth, m_screenHeight);
	initLevel();
	m_controller.init(&m_SOL_cam, &m_player, p_levels);
	m_pathfinder.init(p_levels[m_currentLevel]->getNodeField(), TILE_WIDTH);
}

//Initialise the game content
void Scene::initLevel()
{	
	p_levels.push_back(new Level("Levels/level3.txt"));
	
	m_player.init(PLAYER_SPEED, p_levels[m_currentLevel]->getStartPlayerPosition());
	//Passes reference of player to the controller. The controller passes a reference of th input manager to the player.
	//Anything taking direct input will need to a reference to the input manager.

	p_humans.push_back(&m_player);
	
	std::mt19937 randomEngine;
	randomEngine.seed((unsigned int)time(nullptr));
	std::uniform_int_distribution<int> randX(2, p_levels[m_currentLevel]->getWidth() - 2);
	std::uniform_int_distribution<int> randY(2, p_levels[m_currentLevel]->getHeight() - 2);

	//Spawn humans
	for (int i = 0; i < p_levels[m_currentLevel]->getNumHumans(); i++)
	{
		p_humans.push_back(new Human);
		glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH);
		p_humans.back()->init(HUMAN_SPEED, pos, i);
	}

	//Spawn zombies
	const std::vector<glm::vec2>& zombiePositions = p_levels[m_currentLevel]->getStartZombiePositions();
	for (size_t i = 0; i < zombiePositions.size(); i++)
	{
		p_zombies.push_back(new Zombie);
		p_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i], &m_pathfinder);
	}

	m_player.addGun(new Gun("Pistol",    30,    1,    0.0f/*1.0f*/,    1.0f,    20.0f));
	m_player.addGun(new Gun("Shotgun",   60,    20,   0.0f/*10.0f*/,   4.0f,    10.0f));
	m_player.addGun(new Gun("MG",        10,    1,    0.0f/*100.0f*/,  1.5f,    15.0f));
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
        while (m_gameState == Solengine::GameState::PLAY)
		{ 
		    checkVictory();
		
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
	}
}

void Scene::checkVictory()
{
    //todo: _currentLevel++; initLevel(...);

	if (p_zombies.size() == 0)
	{
		std::printf("***Victory!**** \n You killed %d humans and %d zombies. There are %d/%d civilians remainings",
			m_numHumansKilled, m_numZombiesKilled, p_humans.size() - 1, p_levels[m_currentLevel]->getNumHumans());
		Solengine::fatalError("");
	}
}

