#include "Scene.h"

#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>

#include <Solengine/ResourceManager.h>
#include <Solengine/SDLInitialiser.h>
#include <Solengine/ErrorHandler.h>
//#include <Solengine/Vertex.h>

#include "UIButton.h"
#include "UIText.h"
#include "UIIcon.h"

#include "Adept.h"
#include "Fighter.h"
#include "Scout.h"
#include "Rat.h"

//TODO:
// Limit basic camera movement
// Add UI overlay
// Figure out better texturing for UI overlay

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
	for (size_t i = 0; i < p_worldDrawables.size(); i++)
	{
		delete p_worldDrawables[i];
	}
	for (size_t i = 0; i < p_worldDrawables.size(); i++)
	{
		delete p_overlayDrawables[i];
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
	
	m_model.init(m_physicsSpeed, &m_SOL_cam);
	m_view.init(&m_SOL_cam, &m_SOL_uiCam, m_screenWidth, m_screenHeight);

	initScene();
}

//Initialise the game content
void Scene::initScene()
{
	//We're not actually using this, as each drawable holds its own spritebatch. Perhaps we can just drop this?
	std::vector<Solengine::SpriteBatch*> spriteBatches;

	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	p_levels.push_back(new Level(m_SOL_tileLevelLoader.ParseLevelData("Levels/DQlevel1.txt"), spriteBatches.back()));
	p_worldDrawables.push_back(p_levels.back());

	p_tileMap = p_levels[0]->getTileMap();
	m_model.setTileMap(p_tileMap);
	

	//LAYER 1


	//Set walkable highlight
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	UIIcon* walkableHighlight = new UIIcon(0.3f * m_screenWidth, 200, TILE_WIDTH, TILE_WIDTH, spriteBatches.back(), Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID);
	walkableHighlight->setColour({ 0, 150, 0, 150 });
	m_model.setWalkableHighlight(walkableHighlight);
	p_worldDrawables.push_back(walkableHighlight);

	//Set hover highlight
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	UIIcon* hoverHighlight = new UIIcon(0.3f * m_screenWidth, 200, TILE_WIDTH, TILE_WIDTH, spriteBatches.back(), Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID);
	hoverHighlight->setColour({ 200, 200, 200, 100 });
	m_model.setHoverHighlight(hoverHighlight);
	p_worldDrawables.push_back(hoverHighlight);

	//Selection box
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	UIIcon* selectionBox = new UIIcon(0.3f * m_screenWidth, 200, TILE_WIDTH, TILE_WIDTH, spriteBatches.back(), Solengine::ResourceManager::getTexture("Textures/zombie_pack/selection.png").textureID);
	m_model.setSelectionBox(selectionBox);
	p_worldDrawables.push_back(selectionBox);

	//Current unit box
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	UIIcon* currentUnitBox = new UIIcon(0.3f * m_screenWidth, 200, TILE_WIDTH, TILE_WIDTH, spriteBatches.back(), Solengine::ResourceManager::getTexture("Textures/zombie_pack/selection.png").textureID);
	m_model.setCurrentUnitBox(currentUnitBox);
	p_worldDrawables.push_back(currentUnitBox);

	//LAYER 2

	//ADEPT INIT
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	p_units.push_back(new Adept());
	p_units.back()->init(p_levels[m_currentLevel]->getAdeptSpawnCoords(), spriteBatches.back());
	p_worldDrawables.push_back(p_units.back());

	m_model.setCurrentUnit(p_units.back());

	

	//FIGHTER INIT
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	p_units.push_back(new Fighter());
	p_units.back()->init(p_levels[m_currentLevel]->getFighterSpawnCoords(), spriteBatches.back());
	p_worldDrawables.push_back(p_units.back());
	m_model.setSelectedUnit(p_units.back());

	//SCOUT INIT
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	p_units.push_back(new Scout());
	p_units.back()->init(p_levels[m_currentLevel]->getScoutSpawnCoords(), spriteBatches.back());
	p_worldDrawables.push_back(p_units.back());

	//RATS INIT
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	p_units.push_back(new Rat());
	p_units.back()->init(p_levels[m_currentLevel]->getRatSpawnCoords(), spriteBatches.back());
	p_worldDrawables.push_back(p_units.back());

    //LAYER 3 (Overlay)

	//Sets ui backplate
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	p_overlayDrawables.push_back(new UIIcon(20, 0, m_screenWidth, 150, spriteBatches.back(), Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID, { 100, 100, 100, 255 }));

	//Set current icon
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	UIIcon* currentUnitIcon = new UIIcon(0.05f*m_screenWidth, 20, 150, 150, spriteBatches.back());
	m_model.setCurrentUnitIcon(currentUnitIcon);
	p_overlayDrawables.push_back(currentUnitIcon);

	//Set selected icon
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	UIIcon* selectedUnitIcon = new UIIcon(0.6f*m_screenWidth, 20, 150, 150, spriteBatches.back());
	m_model.setSelectedUnitIcon(selectedUnitIcon);
	p_overlayDrawables.push_back(selectedUnitIcon);

	//Set current name
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	p_SOL_spriteFont = new Solengine::Font("Fonts/Roboto-Regular.ttf", 16, spriteBatches.back());
	UIText* currentUnitNameTextBox = new UIText(0.09f*m_screenWidth, 20, 1, p_SOL_spriteFont, "");
	m_model.setCurrentUnitNameTextBox(currentUnitNameTextBox);
	p_overlayDrawables.push_back(currentUnitNameTextBox);

	//Set selected name
	UIText* selectedUnitNameTextBox = new UIText(0.64f*m_screenWidth, 20, 1, p_SOL_spriteFont, "");
	m_model.setSelectedUnitNameTextBox(selectedUnitNameTextBox);
	p_overlayDrawables.push_back(selectedUnitNameTextBox);

	//Set current energy
	UIText* currentUnitEnergy = new UIText(0.15f*m_screenWidth, 80, 1, p_SOL_spriteFont, "Energy: ");
	m_model.setCurrentUnitEnergyText(currentUnitEnergy);
	p_overlayDrawables.push_back(currentUnitEnergy);

	//Set current health
	UIText* currentUnitHealth = new UIText(0.15f*m_screenWidth, 100, 1, p_SOL_spriteFont, "Health: ");
	m_model.setCurrentUnitHealthText(currentUnitHealth);
	p_overlayDrawables.push_back(currentUnitHealth);
	
	//Set selected energy
	UIText* selectedUnitEnergy = new UIText(0.85f*m_screenWidth, 80, 1, p_SOL_spriteFont, "Energy: ");
	m_model.setSelectedEnergyText(selectedUnitEnergy);
	p_overlayDrawables.push_back(selectedUnitEnergy);

    //Set selected health
	UIText* selectedUnitHealth = new UIText(0.85f*m_screenWidth, 100, 1, p_SOL_spriteFont, "Health: ");
	m_model.setSelectedHealthText(selectedUnitHealth);
	p_overlayDrawables.push_back(selectedUnitHealth);
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
			m_gameState = m_model.update(pauseDuration, p_units);

			m_view.update(p_worldDrawables, p_overlayDrawables);

			m_SOL_fpsManager.limitFPS(trackFPS, (int)DESIRED_TICKS_PER_FRAME);
			pauseDuration = 0;
		}


		int pauseClockStart = SDL_GetTicks();
		while (m_gameState == Solengine::GameState::PAUSE)
		{
			//inputVec = m_controller.keyInput();
			//mousePos = m_controller.getMouseScreenPosition();
			//m_gameState = m_controller.pauseStateInput();
		}
		pauseDuration = SDL_GetTicks() - pauseClockStart;
	}
}

