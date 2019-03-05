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
	_screenWidth(1200),
	_screenHeight(600),
	_gameState(GameState::PLAY),
	_fpsMax(80),
	_announceInConsoleFPS(true),
	_player(nullptr),
	_numHumansKilled(0),
	_numZombiesKilled(0)
{

}

//Destructor
MainGame::~MainGame()
{
	for (size_t i = 0; i < _levels.size(); i++)
	{
		delete _levels[i];
	}
	for (size_t i = 0; i < _humans.size(); i++) 
	{
		delete _humans[i];
	}
	for (size_t i = 0; i < _zombies.size(); i++) 
	{
		delete _zombies[i];
	}
}

//Runs the game
void MainGame::run()
{
	initSystems();
	initLevel();

	gameLoop();
}

//Initialise SDL, glew, OpenGL, and shaders
void MainGame::initSystems()
{
	Solengine::sdlInit();

	_SOL_window.create("Zom", _screenWidth, _screenHeight, 0);

	initShaders();

	_SOL_agentSpriteBatch.init();

	_SOL_cam.init(_screenWidth, _screenHeight);

	_SOL_fpsManager.init(_fpsMax);
}

//Compile and link shaders  -- Should I bother having this in an extra function?
void MainGame::initShaders()
{
	_SOL_shaderProgram.compileShaders("Shaders/colourShading.vert", "Shaders/colourShading.frag");
	_SOL_shaderProgram.addAttribute("vertexPosition");
	_SOL_shaderProgram.addAttribute("vertexColour");
	_SOL_shaderProgram.addAttribute("vertexUV");
	_SOL_shaderProgram.linkShaders();
}

//Initialise the game content
void MainGame::initLevel()
{	
	_levels.push_back(new Level("Levels/level1.txt"));
	_currentLevel = 0;

	_player = new Player();
	_player->init(PLAYER_SPEED, _levels[_currentLevel]->getStartPlayerPosition(), &_SOL_inputManager, &_SOL_cam, &_bullets);

	_humans.push_back(_player);

	std::mt19937 randomEngine;
	randomEngine.seed((unsigned int)time(nullptr));
	std::uniform_int_distribution<int> randX(2, _levels[_currentLevel]->getWidth() - 2);
	std::uniform_int_distribution<int> randY(2, _levels[_currentLevel]->getHeight() - 2);

	//Spawn humans
	for (int i = 0; i < _levels[_currentLevel]->getNumHumans(); i++)
	{
		_humans.push_back(new Human);
		glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH);
		_humans.back()->init(HUMAN_SPEED, pos);
	}

	//Spawn zombies
	const std::vector<glm::vec2>& zombiePositions = _levels[_currentLevel]->getStartZombiePositions();
	for (size_t i = 0; i < zombiePositions.size(); i++)
	{
		_zombies.push_back(new Zombie);
		_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i]);
	}

	//Give player guns
	_player->addGun(new Gun("Pistol", 30, 1, 1.0f, 1.0f, 20.0f));
	_player->addGun(new Gun("Shotgun", 60, 20, 10.0f, 4.0f, 10.0f));
	_player->addGun(new Gun("MG", 10, 1, 1.5f, 200.0f, 15.0f));
}


 //Game loop
void MainGame::gameLoop()
{
	const float DESIRED_FRAMETIME = 1000 / _fpsMax;
	const int MAX_PHYSICS_STEPS = 6;
	const float MAX_DELTA_TIME = 1.0f;
	float prevTicks = SDL_GetTicks();
	//When initialised to true, this enables fps console announcing
	bool trackFPS = _announceInConsoleFPS;

	while (_gameState != GameState::EXIT)
	{
		//For calculating and imiting FPS
		_SOL_fpsManager.begin();

		checkVictory();
		processInput();	

		std::tuple<float, float> deltaTimeAndTotalTicks = getDeltaTimeAndTotalTicks(DESIRED_FRAMETIME, prevTicks);
		prevTicks = std::get<1>(deltaTimeAndTotalTicks);
		updatePhysics(std::get<0>(deltaTimeAndTotalTicks), MAX_PHYSICS_STEPS, MAX_DELTA_TIME);
	
		_SOL_cam.setPosition(_player->getPosition());
		_SOL_cam.update();

		drawGame();

		//Calculates, announces, and limits FPS
		_SOL_fpsManager.end(trackFPS);
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

	if (_zombies.size() == 0)
	{
		std::printf("***Victory!**** \n You killed %d humans and %d zombies. There are %d/%d civilians remainings",
			_numHumansKilled, _numZombiesKilled, _humans.size() - 1, _levels[_currentLevel]->getNumHumans());
		Solengine::fatalError("");
	}
}

//Check for pending events, and closes SDL program if the event is a change in GameState.
void MainGame::processInput()
{
	SDL_Event evnt;

	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_SOL_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_SOL_inputManager.keyDown(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_SOL_inputManager.keyUp(evnt.button.button);
			break;
		case SDL_KEYDOWN:
			_SOL_inputManager.keyDown(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_SOL_inputManager.keyUp(evnt.key.keysym.sym);
			break;
		}
	}

	if (_SOL_inputManager.key(SDLK_q))
	{
		_SOL_cam.setScale(_SOL_cam.getScale() + SCALE_SPEED);
	}
	if (_SOL_inputManager.key(SDLK_e))
	{
		_SOL_cam.setScale(_SOL_cam.getScale() - SCALE_SPEED);
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
	for (size_t i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->move(_humans, _zombies, deltaTime);
	}

	for (size_t i = 0; i < _humans.size(); i++)
	{
		//Remember, the player is a human. Player redefines move slightly!
		_humans[i]->move(_humans, _zombies, deltaTime);
	}

	//zombie collision
	for (size_t i = 0; i < _zombies.size(); i++)
	{
		//zombie level
		_zombies[i]->collisionWithLevel(_levels[_currentLevel]->getLevelData());
		//zombie zombie
		for (size_t j = i + 1; j < _zombies.size(); j++)
		{
			_zombies[i]->collisionWithAgent(_zombies[j]);
		}
		//zombie human
		for (size_t j = 0; j < _humans.size(); j++)
		{
			if (_zombies[i]->collisionWithAgent(_humans[j]))
			{
				_zombies.push_back(new Zombie);
				_zombies.back()->init(ZOMBIE_SPEED, _humans[j]->getPosition());
				delete _humans[j];
				_humans[j] = _humans.back();
				_humans.pop_back();
			}
		}
		//zombie player (loss condition)
		if (_zombies[i]->collisionWithAgent(_player))
		{
			Solengine::fatalError("You lose");
		}
	}

	//human collision
	for (size_t i = 0; i < _humans.size(); i++)
	{
		//human level
		_humans[i]->collisionWithLevel(_levels[_currentLevel]->getLevelData());
		//human human
		for (size_t j = i + 1; j < _humans.size(); j++)
		{
			_humans[i]->collisionWithAgent(_humans[j]);
		}
	}
}

void MainGame::updateBullets(float deltaTime)
{
	for (size_t i = 0; i < _bullets.size(); i++)
	{
		bool bulletRemoved = false;
		_bullets[i].move(deltaTime);

		if (_bullets[i].collisionWithWorld(_levels[_currentLevel]->getLevelData()))
		{
			_bullets[i] = _bullets.back();
			_bullets.pop_back();
			i--;
			bulletRemoved = true;
		}

		if (!bulletRemoved)
		{
			for (size_t j = 0; j < _zombies.size(); j++)
			{
				if (_bullets[i].collisionWithAgent(_zombies[j]))
				{
					if (_zombies[j]->applyDamage(_bullets[i].getDamage()))
					{
						//True on zombie death
						delete _zombies[j];
						_zombies[j] = _zombies.back();
						_zombies.pop_back();
						j--;
						_numZombiesKilled++;
					}

					//Removes the bullet
					_bullets[i] = _bullets.back();
					_bullets.pop_back();
					i--;
					bulletRemoved = true;

					//Bullet died, no need for more zombie loops
					break;
				}
			}
		}

		if (!bulletRemoved)
		{
			for (size_t j = 1; j < _humans.size(); j++)
			{
				if (_bullets[i].collisionWithAgent(_humans[j]))
				{
					if (_humans[j]->applyDamage(_bullets[i].getDamage()))
					{
						//Zombie death when this returns true
						delete _humans[j];
						_humans[j] = _humans.back();
						_humans.pop_back();
						j--;
						_numHumansKilled++;
					}

					//Removes the bullet
					_bullets[i] = _bullets.back();
					_bullets.pop_back();
					i--;
					//Bullet died, no need for more zombie loops
					break;
				}
			}
		}
	}
}

void MainGame::drawGame()
{
	//Set base depth
	glClearDepth(1.0);
	//Clear colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_SOL_shaderProgram.use();

	//DrawCode, optional? Tells it to use texture unit 0
	glActiveTexture(GL_TEXTURE0);

	//Shader uses texture 0
	GLint textureUniform = _SOL_shaderProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	//Grab camera matrix
	glm::mat4 projectionMatrix = _SOL_cam.getCameraMatrix();
	GLint pUniform = _SOL_shaderProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	//Draw level
	_levels[_currentLevel]->draw();

	
	_SOL_agentSpriteBatch.begin();

	glm::vec2 agentDims(AGENT_RADIUS * 2.0f);

	//Draw humans
	for (size_t i = 0; i < _humans.size(); i++)
	{
		if (_SOL_cam.isBoxInView(_humans[i]->getPosition(), agentDims))
		{
           	_humans[i]->draw(_SOL_agentSpriteBatch);
		}
	}

	//Draw zombies
	for (size_t i = 0; i < _zombies.size(); i++)
	{
		if (_SOL_cam.isBoxInView(_zombies[i]->getPosition(), agentDims))
		{
			_zombies[i]->draw(_SOL_agentSpriteBatch);
		}
	}

	//Draw bullets
	for (size_t i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].draw(_SOL_agentSpriteBatch);
	}

	// called agent sprite batch but not just for agents
	_SOL_agentSpriteBatch.end();

	_SOL_agentSpriteBatch.renderBatch();

	_SOL_shaderProgram.unuse();

	_SOL_window.swapBuffer();
}

