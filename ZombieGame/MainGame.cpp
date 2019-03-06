#include "MainGame.h"

#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
//#include <tuple>

#include <Solengine/ResourceManager.h>
#include <Solengine/SDLInitialiser.h>
#include <Solengine/ErrorHandler.h>

#include "Zombie.h"
#include "Gun.h"


//Move random engine to Solengine?
//init vs constructors?
//m_xxxx for members
//stack as much as possible over heap for faster access

//NTS: It's okay to have global variables if they're constant
const float HUMAN_SPEED = 1.0f;
const float ZOMBIE_SPEED = 1.2f;
const float PLAYER_SPEED = 10.0f;

//Constructor will initialise private member variables
MainGame::MainGame() :
	m_screenWidth(1200),
	m_screenHeight(600),
	m_gameState(Solengine::GameState::PLAY),
	m_fpsMax(60),
	m_announceInConsoleFPS(true),
	m_numHumansKilled(0),
	m_numZombiesKilled(0)
{

}

//Destructor
MainGame::~MainGame()
{
	for (size_t i = 0; i < mp_levels.size(); i++)
	{
		delete mp_levels[i];
	}
	for (size_t i = 1; i < mp_humans.size(); i++) 
	{
		delete mp_humans[i];
	}
	for (size_t i = 0; i < mp_zombies.size(); i++) 
	{
		delete mp_zombies[i];
	}
}

//Runs the game
void MainGame::run()
{
	initSystems();
	gameLoop();
}

//Initialise SDL, glew, OpenGL, shaders, fps manager and level
void MainGame::initSystems()
{
	Solengine::initialiseSDL();
	m_view.init(&m_player, m_screenWidth, m_screenHeight);
	m_controller.init(&m_view);
	m_SOL_fpsManager.init(m_fpsMax);
	initLevel();
}

//Initialise the game content
void MainGame::initLevel()
{	
	mp_levels.push_back(new Level("Levels/level1.txt"));
	m_currentLevel = 0;

	m_player.init(PLAYER_SPEED, mp_levels[m_currentLevel]->getStartPlayerPosition(), &mm_bullets);
	//Passes reference of player to the controller. The controller passes a reference of th input manager to the player.
	//Anything taking direct input will need to a reference to the input manager.
	m_controller.initPlayer(&m_player);
	//_view.playerInit();

	mp_humans.push_back(&m_player);

	std::mt19937 randomEngine;
	randomEngine.seed((unsigned int)time(nullptr));
	std::uniform_int_distribution<int> randX(2, mp_levels[m_currentLevel]->getWidth() - 2);
	std::uniform_int_distribution<int> randY(2, mp_levels[m_currentLevel]->getHeight() - 2);

	//Spawn humans
	for (int i = 0; i < mp_levels[m_currentLevel]->getNumHumans(); i++)
	{
		mp_humans.push_back(new Human);
		glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH);
		mp_humans.back()->init(HUMAN_SPEED, pos);
	}

	//Spawn zombies
	const std::vector<glm::vec2>& zombiePositions = mp_levels[m_currentLevel]->getStartZombiePositions();
	for (size_t i = 0; i < zombiePositions.size(); i++)
	{
		mp_zombies.push_back(new Zombie);
		mp_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i]);
	}

	//Give player guns
	m_player.addGun(new Gun("Pistol", 30, 1, 1.0f, 1.0f, 20.0f));
	m_player.addGun(new Gun("Shotgun", 60, 20, 10.0f, 4.0f, 10.0f));
	m_player.addGun(new Gun("MG", 10, 1, 1.5f, 200.0f, 15.0f));
}

 //Game loop
void MainGame::gameLoop()
{
	const float DESIRED_FRAMETIME = 1000 / m_fpsMax;
	const int MAX_PHYSICS_STEPS = 6;
	const float MAX_DELTA_TIME = 1.0f;
	float prevTicks = SDL_GetTicks();
	//When initialised to true, this enables fps console announcing
	bool trackFPS = m_announceInConsoleFPS;

	while (m_gameState != Solengine::GameState::EXIT)
	{
		//For calculating and imiting FPS
		m_SOL_fpsManager.begin();

		checkVictory();
		
		//handles input
		m_gameState = m_controller.processInput();	

		std::tuple<float, float> deltaTimeAndTotalTicks = getDeltaTimeAndTotalTicks(DESIRED_FRAMETIME, prevTicks);
		prevTicks = std::get<1>(deltaTimeAndTotalTicks);
		updatePhysics(std::get<0>(deltaTimeAndTotalTicks), MAX_PHYSICS_STEPS, MAX_DELTA_TIME);
	
		//handles rendering
		m_view.update(mp_humans, mp_zombies, mp_levels, mm_bullets);

		//Calculates, announces, and limits FPS
		m_SOL_fpsManager.end(trackFPS);
	}
}

//returns delta time and the total ticks
std::tuple<float, float> MainGame::getDeltaTimeAndTotalTicks(float desiredFrametime, float prevTicks)
{
	float totalTicks = SDL_GetTicks();
	float frameTicks = totalTicks - prevTicks;
	return std::make_tuple(frameTicks / desiredFrametime, totalTicks);
}

void MainGame::checkVictory()
{
    //todo: _currentLevel++; initLevel(...);

	if (mp_zombies.size() == 0)
	{
		std::printf("***Victory!**** \n You killed %d humans and %d zombies. There are %d/%d civilians remainings",
			m_numHumansKilled, m_numZombiesKilled, mp_humans.size() - 1, mp_levels[m_currentLevel]->getNumHumans());
		Solengine::fatalError("");
	}
}

void MainGame::updatePhysics(float totalDeltaTime, float MAX_PHYSICS_STEPS, float MAX_DELTA_TIME)
{
	int i = 0;

	while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS)
	{
		float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
		updateAgents(deltaTime);
		updateBullets(deltaTime);
		totalDeltaTime -= deltaTime;
		i++;
	}
}

void MainGame::updateAgents(float deltaTime)
{
	for (size_t i = 0; i < mp_zombies.size(); i++)
	{
		mp_zombies[i]->move(mp_humans, mp_zombies, deltaTime);
	}

	for (size_t i = 0; i < mp_humans.size(); i++)
	{
		//Remember, the player is a human. Player redefines move slightly!
		mp_humans[i]->move(mp_humans, mp_zombies, deltaTime);
	}

	//zombie collision
	for (size_t i = 0; i < mp_zombies.size(); i++)
	{
		//zombie level
		mp_zombies[i]->collisionWithLevel(mp_levels[m_currentLevel]->getLevelData());
		//zombie zombie
		for (size_t j = i + 1; j < mp_zombies.size(); j++)
		{
			mp_zombies[i]->collisionWithAgent(mp_zombies[j]);
		}
		//zombie human
		for (size_t j = 1; j < mp_humans.size(); j++)
		{
			if (mp_zombies[i]->collisionWithAgent(mp_humans[j]))
			{
				mp_zombies.push_back(new Zombie);
				mp_zombies.back()->init(ZOMBIE_SPEED, mp_humans[j]->getPosition());
				delete mp_humans[j];
				mp_humans[j] = mp_humans.back();
				mp_humans.pop_back();
			}
		}

		//zombie player (loss condition)
		if (mp_zombies[i]->collisionWithAgent(&m_player))
		{
			std::printf("***DEFEAT!***");
			Solengine::fatalError("");
		}
	}

	//human collision
	for (size_t i = 0; i < mp_humans.size(); i++)
	{
		//human level
		mp_humans[i]->collisionWithLevel(mp_levels[m_currentLevel]->getLevelData());
		//human human
		for (size_t j = i + 1; j < mp_humans.size(); j++)
		{
			mp_humans[i]->collisionWithAgent(mp_humans[j]);
		}
	}
}

void MainGame::updateBullets(float deltaTime)
{
	for (size_t i = 0; i < mm_bullets.size(); i++)
	{
		bool bulletRemoved = false;
		mm_bullets[i].move(deltaTime);

		if (mm_bullets[i].collisionWithWorld(mp_levels[m_currentLevel]->getLevelData()))
		{
			mm_bullets[i] = mm_bullets.back();
			mm_bullets.pop_back();
			i--;
			bulletRemoved = true;
		}

		if (!bulletRemoved)
		{
			for (size_t j = 0; j < mp_zombies.size(); j++)
			{
				if (mm_bullets[i].collisionWithAgent(mp_zombies[j]))
				{
					if (mp_zombies[j]->applyDamage(mm_bullets[i].getDamage()))
					{
						//True on zombie death
						delete mp_zombies[j];
						mp_zombies[j] = mp_zombies.back();
						mp_zombies.pop_back();
						j--;
						m_numZombiesKilled++;
					}

					//Removes the bullet
					mm_bullets[i] = mm_bullets.back();
					mm_bullets.pop_back();
					i--;
					bulletRemoved = true;

					//Bullet died, no need for more zombie loops
					break;
				}
			}
		}

		if (!bulletRemoved)
		{
			for (size_t j = 1; j < mp_humans.size(); j++)
			{
				if (mm_bullets[i].collisionWithAgent(mp_humans[j]))
				{
					if (mp_humans[j]->applyDamage(mm_bullets[i].getDamage()))
					{
						//Zombie death when this returns true
						delete mp_humans[j];
						mp_humans[j] = mp_humans.back();
						mp_humans.pop_back();
						j--;
						m_numHumansKilled++;
					}

					//Removes the bullet
					mm_bullets[i] = mm_bullets.back();
					mm_bullets.pop_back();
					i--;
					//Bullet died, no need for more zombie loops
					break;
				}
			}
		}
	}
}
