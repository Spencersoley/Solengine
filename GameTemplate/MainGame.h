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
#include <tuple>

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

	void drawGame();


	int _screenWidth;
	int _screenHeight;
	GameState _gameState;
	bool _trackFPS;
	int _currentLevel;

	//SOL helps indicate engine use
	Solengine::GLSLProgram _SOL_shaderProgram;
	Solengine::FPSManager _SOL_fpsManager;
	Solengine::Window _SOL_window;
	Solengine::Camera2D _SOL_cam;
	Solengine::SpriteBatch _SOL_agentSpriteBatch;
	Solengine::InputManager _SOL_inputManager;

	int _fpsMax;

	int _numHumansKilled;
	int _numZombiesKilled;


	Uint32 _frameTime;
};

