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
	_fpsMax(60),
	_trackFPS(false)
{

}

//Destructor
MainGame::~MainGame()
{
	/* Delete pointers in destructor 
	
	for (size_t i = 0; i < _POINTERS.size(); i++)
	{
		delete _levels[i];
	}*/

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

}


//Game loop
void MainGame::gameLoop()
{
	const float DESIRED_FRAMETIME = 1000 / _fpsMax;
	const int MAX_PHYSICS_STEPS = 6;
	const float MAX_DELTA_TIME = 1.0f;
	float prevTicks = SDL_GetTicks();
	bool track = _trackFPS;

	while (_gameState != GameState::EXIT)
	{
		//For measuring frametime
		_SOL_fpsManager.begin();

		checkVictory();
		processInput();

		std::tuple<float, float> deltaTimeAndTotalTicks = getDeltaTimeAndTotalTicks(DESIRED_FRAMETIME, prevTicks);
		prevTicks = std::get<1>(deltaTimeAndTotalTicks);
		updatePhysics(std::get<0>(deltaTimeAndTotalTicks), MAX_PHYSICS_STEPS, MAX_DELTA_TIME);

		
		_SOL_cam.update();

		drawGame();

		//Calculates, announces, and limits FPS
		_SOL_fpsManager.end(track);
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
	//Victory condition, perhaps reinitialise a level?
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

	/*
	if (_SOL_inputManager.key(SDLK_q))
	{
		_SOL_cam.setScale(_SOL_cam.getScale() + SCALE_SPEED);
	}
	if (_SOL_inputManager.key(SDLK_e))
	{
		_SOL_cam.setScale(_SOL_cam.getScale() - SCALE_SPEED);
	}
	*/
}

void MainGame::updatePhysics(float totalDeltaTime, float MAX_PHYSICS_STEPS, float MAX_DELTA_TIME)
{
	int i = 0;

	while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS)
	{
		float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
		/*updateAgents(deltaTime);*/
		totalDeltaTime -= deltaTime;
		i++;
	}
}

void MainGame::updateAgents(float deltaTime)
{
	
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

	//Draw 
	/*entitypointer->draw();*/


	_SOL_agentSpriteBatch.begin();

    /*some drawing loops
	
	for (size_t i = 0; i < _agents.size(); i++)
	{
		if (_SOL_cam.isBoxInView(_agents[i]->getPosition(), agentDimensions))
		{
           	_agents[i]->draw(_SOL_agentSpriteBatch);
		}
	}
	
	*/

	//called agent sprite batch but not just for agents
	_SOL_agentSpriteBatch.end();

	_SOL_agentSpriteBatch.renderBatch();

	_SOL_shaderProgram.unuse();

	_SOL_window.swapBuffer();
}

