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

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>

#include "Bullet.h"
#include "Level.h"
#include "Player.h"
#include "View.h"

class Zombie;

enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	void initSystems();
	void initShaders();
	void initLevel();

	void gameLoop();

	std::tuple<float, float> getDeltaTimeAndTotalTicks(float desiredFrametime, float prevTicks);
	void checkVictory();
	void processInput();
	void updatePhysics(float totalDeltaTime, float MAX_PHYSICS_STEPS, float MAX_DELTA_TIME);

	void updateAgents(float deltaTime);
	void updateBullets(float deltaTime);


	int _screenWidth;
	int _screenHeight;
	GameState _gameState;
	bool _announceInConsoleFPS;
	int _currentLevel;

	//SOL helps indicate engine use
	Solengine::FPSManager _SOL_fpsManager;
	Solengine::InputManager _SOL_inputManager;

	View view;

	std::vector<Bullet> _bullets;
	std::vector<Level*> _levels;
	std::vector<Human*> _humans;
	std::vector<Zombie*> _zombies;
	
	Player* _player;

	int _fpsMax;

	int _numHumansKilled;
	int _numZombiesKilled;


	Uint32 _frameTime;
};

