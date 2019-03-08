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
//stack as much as possible over heap for faster access
//clean controller up
//pause
//move all control to controller
//can we separate 'model'?

//NTS: It's okay to have global variables if they're constant
const float HUMAN_SPEED = 1.0f;
const float ZOMBIE_SPEED = 1.2f;
const float PLAYER_SPEED = 10.0f;

//Constructor will initialise private member variables
Scene::Scene() :
	m_screenWidth(1200),
	m_screenHeight(600),
	m_gameState(Solengine::GameState::PLAY),
	m_currentLevel(0),
	m_fpsMax(600),
	m_gameSpeed(0.05f),
	m_announceInConsoleFPS(true),
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
	m_view.init(&m_player, m_screenWidth, m_screenHeight);
	m_controller.init(&m_view);
	initLevel();
}

//Initialise the game content
void Scene::initLevel()
{	
	p_levels.push_back(new Level("Levels/level1.txt"));
	

	m_player.init(PLAYER_SPEED, p_levels[m_currentLevel]->getStartPlayerPosition());
	//Passes reference of player to the controller. The controller passes a reference of th input manager to the player.
	//Anything taking direct input will need to a reference to the input manager.
	m_controller.initPlayer(&m_player);
	//_view.playerInit();

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
		p_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i]);
	}

	//Give player guns
	m_player.addGun(new Gun("Pistol", 30, 1, 1.0f, 1.0f, 20.0f));
	m_player.addGun(new Gun("Shotgun", 60, 20, 10.0f, 4.0f, 10.0f));
	m_player.addGun(new Gun("MG", 10, 1, 1.5f, 200.0f, 15.0f));
}

 //Game loop
void Scene::gameLoop()
{
	const float DESIRED_TICKS_PER_FRAME = 1000 / (float)m_fpsMax;
	const int MAX_PHYSICS_STEPS = 5;
	const float MAX_DELTA_TIME = 1.0f;
	static int pauseDuration = 0;
	//When initialised to true, this enables fps console announcing
	bool trackFPS = m_announceInConsoleFPS;

	while (m_gameState != Solengine::GameState::EXIT)
	{    
        while (m_gameState == Solengine::GameState::PLAY)
		{ 
		    checkVictory();
		
		    //handles input
		    m_gameState = m_controller.playStateInput();

	        updatePhysics(MAX_PHYSICS_STEPS, MAX_DELTA_TIME, pauseDuration);

	        //handles rendering
		    m_view.update(p_humans, p_zombies, p_levels, m_bullets);

		    //Calculates, announces, and limits FPS
		    m_SOL_fpsManager.limitFPS(trackFPS, (int)DESIRED_TICKS_PER_FRAME);
			//std::cout << "---PLAY---" << std::endl;
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

Uint32 Scene::getDeltaTicks()
{
	static Uint32 prevTicks = SDL_GetTicks();
	Uint32 deltaTicks = SDL_GetTicks() - prevTicks;
	prevTicks = SDL_GetTicks();
	return deltaTicks;
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

void Scene::updatePhysics(float MAX_PHYSICS_STEPS, float MAX_DELTA_TIME, int pauseDuration)
{
	float adjustedDeltaTicks = (getDeltaTicks() - pauseDuration) * m_gameSpeed;
	updateAgents(adjustedDeltaTicks);
	updateBullets(adjustedDeltaTicks);

	/*
	int i = 0;
	while (adjustedDeltaTicks > 0.0f && i < MAX_PHYSICS_STEPS)
	{
		float deltaTicks = std::min(adjustedDeltaTicks, MAX_DELTA_TIME);
		updateAgents(deltaTicks);
		updateBullets(deltaTicks);
		adjustedDeltaTicks -= deltaTicks;
		i++;
	}
	*/
}

void Scene::updateAgents(float adjustedDeltaTicks)
{
	m_globalFrameCount++;

	for (size_t i = 0; i < p_zombies.size(); i++)
	{
		p_zombies[i]->move(p_humans, p_zombies, adjustedDeltaTicks, m_globalFrameCount);
	}

	m_player.move(p_humans, p_zombies, m_bullets, adjustedDeltaTicks);

	for (size_t i = 1; i < p_humans.size(); i++)
	{
		//Remember, the player is a human[0]. Player redefines move slightly!
		p_humans[i]->move(p_humans, p_zombies, adjustedDeltaTicks, m_globalFrameCount);
		if (m_globalFrameCount > 359) m_globalFrameCount = 0;
	}

	//zombie collision
	for (size_t i = 0; i < p_zombies.size(); i++)
	{
		//zombie level
		p_zombies[i]->collisionWithLevel(p_levels[m_currentLevel]->getLevelData());
		//zombie zombie
		for (size_t j = i + 1; j < p_zombies.size(); j++)
		{
			p_zombies[i]->collisionWithAgent(p_zombies[j]);
		}
		//zombie human
		for (size_t j = 1; j < p_humans.size(); j++)
		{
			if (p_zombies[i]->collisionWithAgent(p_humans[j]))
			{
				p_zombies.push_back(new Zombie);
				p_zombies.back()->init(ZOMBIE_SPEED, p_humans[j]->getPosition());
				delete p_humans[j];
				p_humans[j] = p_humans.back();
				p_humans.pop_back();
			}
		}

		//zombie player (loss condition)
		if (p_zombies[i]->collisionWithAgent(&m_player))
		{
			std::printf("***DEFEAT!***");
			Solengine::fatalError("");
		}
	}

	//human collision
	for (size_t i = 0; i < p_humans.size(); i++)
	{
		//human level
		p_humans[i]->collisionWithLevel(p_levels[m_currentLevel]->getLevelData());
		//human human
		for (size_t j = i + 1; j < p_humans.size(); j++)
		{
			p_humans[i]->collisionWithAgent(p_humans[j]);
		}
	}
}

void Scene::updateBullets(float adjustedDeltaTicks)
{
	for (size_t i = 0; i < m_bullets.size(); i++)
	{
		bool bulletRemoved = false;
		m_bullets[i].move(adjustedDeltaTicks);

		if (m_bullets[i].collisionWithWorld(p_levels[m_currentLevel]->getLevelData()))
		{
			m_bullets[i] = m_bullets.back();
			m_bullets.pop_back();
			i--;
			bulletRemoved = true;
		}

		if (!bulletRemoved)
		{
			for (size_t j = 0; j < p_zombies.size(); j++)
			{
				if (m_bullets[i].collisionWithAgent(p_zombies[j]))
				{
					if (p_zombies[j]->applyDamage(m_bullets[i].getDamage()))
					{
						//True on zombie death
						delete p_zombies[j];
						p_zombies[j] = p_zombies.back();
						p_zombies.pop_back();
						j--;
						m_numZombiesKilled++;
					}

					//Removes the bullet
					m_bullets[i] = m_bullets.back();
					m_bullets.pop_back();
					i--;
					bulletRemoved = true;

					//Bullet died, no need for more zombie loops
					break;
				}
			}
		}

		if (!bulletRemoved)
		{
			for (size_t j = 1; j < p_humans.size(); j++)
			{
				if (m_bullets[i].collisionWithAgent(p_humans[j]))
				{
					if (p_humans[j]->applyDamage(m_bullets[i].getDamage()))
					{
						//Zombie death when this returns true
						delete p_humans[j];
						p_humans[j] = p_humans.back();
						p_humans.pop_back();
						j--;
						m_numHumansKilled++;
					}

					//Removes the bullet
					m_bullets[i] = m_bullets.back();
					m_bullets.pop_back();
					i--;
					//Bullet died, no need for more zombie loops
					break;
				}
			}
		}
	}
}
