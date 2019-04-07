#include "Scene.h"

#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>

#include <Solengine/ResourceManager.h>
#include <Solengine/SDLInitialiser.h>
#include <Solengine/ErrorHandler.h>

#include "UIButton.h"
#include "UIText.h"
#include "UIIcon.h"

#include "Adept.h"
#include "Fighter.h"
#include "Scout.h"

//TODO:
// Limit basic camera movement
// Add UI overlay
// Figure out better texturing for UI overlay
// Add unit selection

// Can we move level sprite batch to view?

//Constructor will initialise private member variables
Scene::Scene() :
	m_screenWidth(1200),
	m_screenHeight(600),
	m_gameState(Solengine::GameState::PLAY),
	m_currentLevel(0),
	m_turnCounter(0),
	m_fpsMax(60),
	m_physicsSpeed(0.02f),
	m_announceFPS(false)

{
}

//Destructor
Scene::~Scene()
{
	for (size_t i = 0; i < p_levels.size(); i++)
	{
		delete p_levels[i];
	}
	for (size_t i = 0; i < p_units.size(); i++)
	{
		delete p_units[i];
	}
	for (size_t i = 0; i < p_UIElements.size(); i++)
	{
		delete p_UIElements[i];
	}
	for (size_t i = 0; i < p_SOL_spriteBatches.size(); i++)
	{
		delete p_SOL_spriteBatches[i];
	}

	delete p_SOL_spriteFont;
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
	
	m_model.init(m_physicsSpeed);
	m_view.init(&m_SOL_cam, &m_SOL_uiCam, m_screenWidth, m_screenHeight);
	m_controller.init(&m_SOL_cam, &m_model);

	initScene();

}

//Initialise the game content
void Scene::initScene()
{

	//Set level
	p_SOL_spriteBatches.push_back(new Solengine::SpriteBatch());
	p_SOL_spriteBatches.back()->init();
	p_levels.push_back(new Level(m_SOL_tileLevelLoader.ParseLevelData("Levels/DQlevel1.txt"), p_SOL_spriteBatches.back()));

	//ADEPT INIT
	p_SOL_spriteBatches.push_back(new Solengine::SpriteBatch());
	p_SOL_spriteBatches.back()->init();
	p_units.push_back(new Adept());
	p_units.back()->init(p_levels[m_currentLevel]->getAdeptSpawnCoords(), p_SOL_spriteBatches.back());
	p_currentUnit = p_units[0];

	//FIGHTER INIT
	p_SOL_spriteBatches.push_back(new Solengine::SpriteBatch());
	p_SOL_spriteBatches.back()->init();
	p_units.push_back(new Fighter());
	p_units.back()->init(p_levels[m_currentLevel]->getFighterSpawnCoords(), p_SOL_spriteBatches.back());

	//SCOUT INIT
	p_SOL_spriteBatches.push_back(new Solengine::SpriteBatch());
	p_SOL_spriteBatches.back()->init();
	p_units.push_back(new Scout());
	p_units.back()->init(p_levels[m_currentLevel]->getScoutSpawnCoords(), p_SOL_spriteBatches.back());

	//UI//
	
	//Sets ui backplate
	p_SOL_spriteBatches.push_back(new Solengine::SpriteBatch());
	p_SOL_spriteBatches.back()->init();
	p_UIElements.push_back(new UIIcon(20, 0, m_screenWidth, 150, Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID, p_SOL_spriteBatches.back()));

	//
	//p_SOL_spriteBatches.push_back(new Solengine::SpriteBatch());
	//p_SOL_spriteBatches.back()->init();
	//p_UIElements.push_back(new UIButton(40, 80, 150, 150, Solengine::ResourceManager::getTexture("Textures/zombie_pack/circle2.png").textureID, p_SOL_spriteBatches.back()));


	//Set current icon
	p_SOL_spriteBatches.push_back(new Solengine::SpriteBatch());
	p_SOL_spriteBatches.back()->init();
	UIIcon* currentUnitIcon = new UIIcon(0.05f*m_screenWidth, 20, 150, 150, p_SOL_spriteBatches.back());
	p_UIElements.push_back(currentUnitIcon);
	m_view.setCurrentUnitIcon(currentUnitIcon);

	//Set selected icon
	p_SOL_spriteBatches.push_back(new Solengine::SpriteBatch());
	p_SOL_spriteBatches.back()->init();
	UIIcon* selectedUnitIcon = new UIIcon(0.6f*m_screenWidth, 20, 150, 150, p_SOL_spriteBatches.back());
	p_UIElements.push_back(selectedUnitIcon);
	m_view.setSelectedUnitIcon(selectedUnitIcon);

	//Set current name
	p_SOL_spriteBatches.push_back(new Solengine::SpriteBatch());
	p_SOL_spriteBatches.back()->init();
	p_SOL_spriteFont = new Solengine::Font("Fonts/Roboto-Regular.ttf", 16, p_SOL_spriteBatches.back());
	UIText* currentUnitNameTextBox = new UIText(0.09f*m_screenWidth, 20, 1, p_SOL_spriteFont, "", 0);
	p_UIElements.push_back(currentUnitNameTextBox);	
	m_view.setCurrentUnitNameTextBox(currentUnitNameTextBox);

	//Set selected name
	UIText* selectedUnitNameTextBox = new UIText(0.64f*m_screenWidth, 20, 1, p_SOL_spriteFont, "", 0);
	p_UIElements.push_back(selectedUnitNameTextBox);
	m_view.setSelectedUnitNameTextBox(selectedUnitNameTextBox);

	//Current stats
	//Current moveset
	//selected stats
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

			m_view.update(p_levels, p_units, p_UIElements, p_currentUnit, p_selectedUnit);


			//if unit is friendly
			m_gameState = m_controller.playStateInput();
			if (m_controller.getIsMouseDown()) setSelected(m_controller.selectionCheck(p_units));
			//else if unit is enemy
			//works through AI LOGIC
			//enemy does stuff and eventually ends its turn
			//

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

