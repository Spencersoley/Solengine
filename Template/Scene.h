#pragma once

#include <Solengine/SDLInitialiser.h>
#include <Solengine/ErrorHandler.h>
#include <Solengine/GLSLProgram.h>
#include <Solengine/GLTexture.h>
#include <Solengine/Window.h>
#include <Solengine/FPSManager.h>
#include <Solengine/TileLevelLoader.h>
#include <Solengine/Camera2D.h>
#include <Solengine/SpriteBatch.h>
#include <Solengine/InputManager.h>
#include <Solengine/GameState.h>

#include "Model.h"
#include "View.h"
#include "Controller.h"

#include "Level.h"

class Scene
{
public:
	Scene();
	~Scene();

	void run();

private:
	void initSystems();
	void initScene();
	void gameLoop();

	Solengine::TileLevelLoader m_SOL_tileLevelLoader;
	Solengine::FPSManager m_SOL_fpsManager;
	Solengine::ICamera* m_SOL_cam = new Solengine::Camera2D;
	Solengine::ICamera* m_SOL_uiCam = new Solengine::Camera2D;
	Model m_model;
	View m_view;
	Controller m_controller;

	std::vector<Level*> p_levels;

	int m_screenWidth;
	int m_screenHeight;
	Solengine::GameState m_gameState;
	int m_currentLevel;
	int m_fpsMax;
	float m_physicsSpeed;
	bool m_announceFPS;
};

