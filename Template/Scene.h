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
#include <Solengine/GameState.h>

#include "Model.h"
#include "View.h"
#include "Controller.h"

class Zombie;

class Scene
{
public:
	Scene();
	~Scene();

	void run();

private:
	void initSystems();
	void initLevel();
	void gameLoop();

	Solengine::FPSManager m_SOL_fpsManager;
	Solengine::Camera2D m_SOL_cam;
	Solengine::Camera2D m_SOL_uiCam;
	Model m_model;
	View m_view;
	Controller m_controller;

	int m_screenWidth;
	int m_screenHeight;
	Solengine::GameState m_gameState;
	int m_currentLevel;
	int m_fpsMax;
	float m_gameSpeed;
	bool m_announceFPS;
};

