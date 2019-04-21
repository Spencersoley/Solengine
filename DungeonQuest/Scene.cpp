#include "Scene.h"

#include "Solengine/ResourceManager.h"
#include "Solengine/SDLInitialiser.h"
#include "Solengine/ErrorHandler.h"

#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>

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
	std::vector<Solengine::Font*> fontBatches;

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
	UIIcon* walkableHighlight = new UIIcon((int)(0.3f * m_screenWidth), 200, TILE_WIDTH, TILE_WIDTH, spriteBatches.back(), Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID);
	walkableHighlight->setColour({ 0, 150, 0, 150 });
	m_model.setWalkableHighlight(walkableHighlight);
	p_worldDrawables.push_back(walkableHighlight);

	//Set hover highlight
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	UIIcon* hoverHighlight = new UIIcon((int)(0.3f * m_screenWidth), 200, TILE_WIDTH, TILE_WIDTH, spriteBatches.back(), Solengine::ResourceManager::getTexture("Textures/zombie_pack/Aim.png").textureID);
	hoverHighlight->setColour({ 200, 200, 200, 100 });
	m_model.setHoverHighlight(hoverHighlight);
	p_worldDrawables.push_back(hoverHighlight);

	//Selection box
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	UIIcon* selectionBox = new UIIcon((int)(0.3f * m_screenWidth), 200, TILE_WIDTH, TILE_WIDTH, spriteBatches.back(), Solengine::ResourceManager::getTexture("Textures/zombie_pack/selection.png").textureID);
	m_model.setSelectionBox(selectionBox);
	p_worldDrawables.push_back(selectionBox);

	//Current unit box
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	UIIcon* currentUnitBox = new UIIcon((int)(0.3f * m_screenWidth), 200, TILE_WIDTH, TILE_WIDTH, spriteBatches.back(), Solengine::ResourceManager::getTexture("Textures/zombie_pack/selection.png").textureID);
	m_model.setCurrentUnitBox(currentUnitBox);
	p_worldDrawables.push_back(currentUnitBox);

	//LAYER 2

	//ADEPT INIT
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	p_units.push_back(new Adept(&m_spellBook));
	p_units.back()->init(p_levels[m_currentLevel]->getAdeptSpawnCoords(), spriteBatches.back());
	
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	UIIcon* hb = new UIIcon(0, 0, (int)(0.5f * TILE_WIDTH), (int)(0.1f * TILE_WIDTH), spriteBatches.back(), Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID);
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	UIIcon* hbb = new UIIcon(0, 0, (int)(0.5f * TILE_WIDTH), (int)(0.1f * TILE_WIDTH), spriteBatches.back(), Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID);
	p_units.back()->setHealthbar(hb, hbb);
	p_worldDrawables.push_back(hbb);
	p_worldDrawables.push_back(hb);
	hb->setColour({ 0, 255, 0, 255 });
	hbb->setColour({ 222, 0, 0, 255 });
	p_worldDrawables.push_back(p_units.back());
	m_model.setCurrentUnit(p_units.back());


	//FIGHTER INIT
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	p_units.push_back(new Fighter(&m_spellBook));
	p_units.back()->init(p_levels[m_currentLevel]->getFighterSpawnCoords(), spriteBatches.back());

	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	hb = new UIIcon(0, 0, (int)(0.5f * TILE_WIDTH), (int)(0.1f * TILE_WIDTH), spriteBatches.back(), Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID);
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	hbb = new UIIcon(0, 0, (int)(0.5f * TILE_WIDTH), (int)(0.1f * TILE_WIDTH), spriteBatches.back(), Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID);
	p_units.back()->setHealthbar(hb, hbb);
	p_worldDrawables.push_back(hbb);
	p_worldDrawables.push_back(hb);
	hb->setColour({ 0, 255, 0, 255 });
	hbb->setColour({ 222, 0, 0, 255 });
	p_worldDrawables.push_back(p_units.back());
	m_model.setSelectedUnit(p_units.back());

	//SCOUT INIT
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	p_units.push_back(new Scout(&m_spellBook));
	p_units.back()->init(p_levels[m_currentLevel]->getScoutSpawnCoords(), spriteBatches.back());

	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	hb = new UIIcon(0, 0, (int)(0.5f * TILE_WIDTH), (int)(0.1f * TILE_WIDTH), spriteBatches.back(), Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID);
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	hbb = new UIIcon(0, 0, (int)(0.5f * TILE_WIDTH), (int)(0.1f * TILE_WIDTH), spriteBatches.back(), Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID);
	p_units.back()->setHealthbar(hb, hbb);
	p_worldDrawables.push_back(hbb);
	p_worldDrawables.push_back(hb);
	hb->setColour({ 0, 255, 0, 255 });
	hbb->setColour({ 222, 0, 0, 255 });
	p_worldDrawables.push_back(p_units.back());

	//RATS INIT
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	p_units.push_back(new Rat(&m_spellBook));
	p_units.back()->init(p_levels[m_currentLevel]->getRatSpawnCoords(), spriteBatches.back());

	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	hb = new UIIcon(0, 0, (int)(0.5f * TILE_WIDTH), (int)(0.1f * TILE_WIDTH), spriteBatches.back(), Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID);
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	hbb = new UIIcon(0, 0, (int)(0.5f * TILE_WIDTH), (int)(0.1f * TILE_WIDTH), spriteBatches.back(), Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID);
	p_units.back()->setHealthbar(hb, hbb);
	p_worldDrawables.push_back(hbb);
	p_worldDrawables.push_back(hb);
	hb->setColour({ 0, 255, 0, 255 });
	hbb->setColour({ 222, 0, 0, 255 });
	p_worldDrawables.push_back(p_units.back());

    //LAYER 3 (Overlay)

	//Sets ui backplate
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	p_overlayDrawables.push_back(new UIIcon(20, 0, m_screenWidth, 150, spriteBatches.back(), Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID, { 100, 100, 100, 255 }));

	//Set current icon
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	UIIcon* currentUnitIcon = new UIIcon((int)(0.05f*m_screenWidth), 20, 150, 150, spriteBatches.back());
	m_model.setCurrentUnitIcon(currentUnitIcon);
	p_overlayDrawables.push_back(currentUnitIcon);

	//Set selected icon
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	UIIcon* selectedUnitIcon = new UIIcon((int)(0.74f*m_screenWidth), 20, 150, 150, spriteBatches.back());
	m_model.setSelectedUnitIcon(selectedUnitIcon);
	p_overlayDrawables.push_back(selectedUnitIcon);

	//Set current name
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	fontBatches.push_back(new Solengine::Font("Fonts/Roboto-Regular.ttf", 16, spriteBatches.back()));
	UIText* currentUnitNameText = new UIText((int)(0.09f*m_screenWidth), 20, 1, fontBatches.back(), "");
	m_model.setCurrentUnitNameText(currentUnitNameText);
	p_overlayDrawables.push_back(currentUnitNameText);

	//Set selected name
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	fontBatches.push_back(new Solengine::Font("Fonts/Roboto-Regular.ttf", 16, spriteBatches.back()));
	UIText* selectedUnitNameText = new UIText((int)(0.78f*m_screenWidth), 20, 1, fontBatches.back(), "");
	m_model.setSelectedUnitNameText(selectedUnitNameText);
	p_overlayDrawables.push_back(selectedUnitNameText);

	//Set current health
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	fontBatches.push_back(new Solengine::Font("Fonts/Roboto-Regular.ttf", 16, spriteBatches.back()));
	UIText* currentUnitHealth = new UIText((int)(0.15f*m_screenWidth), 100, 1, fontBatches.back(), "HP: ");
	m_model.setCurrentUnitHealthText(currentUnitHealth);
	p_overlayDrawables.push_back(currentUnitHealth);

	//Set current energy
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	fontBatches.push_back(new Solengine::Font("Fonts/Roboto-Regular.ttf", 16, spriteBatches.back()));
	UIText* currentUnitEnergy = new UIText((int)(0.15f*m_screenWidth), 80, 1, fontBatches.back(), "NRG: ");
	m_model.setCurrentUnitEnergyText(currentUnitEnergy);
	p_overlayDrawables.push_back(currentUnitEnergy);

	//Set selected energy
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	fontBatches.push_back(new Solengine::Font("Fonts/Roboto-Regular.ttf", 16, spriteBatches.back()));
	UIText* selectedUnitEnergy = new UIText((int)(0.85f*m_screenWidth), 80, 1, fontBatches.back(), "NRG: ");
	m_model.setSelectedEnergyText(selectedUnitEnergy);
	p_overlayDrawables.push_back(selectedUnitEnergy);

    //Set selected health
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	fontBatches.emplace_back(new Solengine::Font("Fonts/Roboto-Regular.ttf", 16, spriteBatches.back()));
	UIText* selectedUnitHealth = new UIText((int)(0.85f*m_screenWidth), 100, 1, fontBatches.back(), "HP: ");
	m_model.setSelectedHealthText(selectedUnitHealth);
	p_overlayDrawables.push_back(selectedUnitHealth);

	//Set attack 1 
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	fontBatches.emplace_back(new Solengine::Font("Fonts/Roboto-Regular.ttf", 16, spriteBatches.back()));
	UIText* spellOneText = new UIText((int)(0.23f*m_screenWidth), 100, 1, fontBatches.back(), " 1: ");
	m_model.setSpellText(spellOneText);
	p_overlayDrawables.push_back(spellOneText);

	//Set attack 2 text
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	fontBatches.emplace_back(new Solengine::Font("Fonts/Roboto-Regular.ttf", 16, spriteBatches.back()));
	UIText* spellTwoText = new UIText((int)(0.23f*m_screenWidth), 80, 1, fontBatches.back(), " 2: ");
	m_model.setSpellText(spellTwoText);
	p_overlayDrawables.push_back(spellTwoText);

	//Set attack 3 text
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	fontBatches.emplace_back(new Solengine::Font("Fonts/Roboto-Regular.ttf", 16, spriteBatches.back()));
	UIText* spellThreeText = new UIText((int)(0.23f*m_screenWidth), 60, 1, fontBatches.back(), " 3: ");
	m_model.setSpellText(spellThreeText);
	p_overlayDrawables.push_back(spellThreeText);

	//Set attack 4 text
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	fontBatches.emplace_back(new Solengine::Font("Fonts/Roboto-Regular.ttf", 16, spriteBatches.back()));
	UIText* spellFourText = new UIText((int)(0.23f*m_screenWidth), 40, 1, fontBatches.back(), " 4: ");
	m_model.setSpellText(spellFourText);
	p_overlayDrawables.push_back(spellFourText);

	//Set attack 1 stats
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	fontBatches.emplace_back(new Solengine::Font("Fonts/Roboto-Regular.ttf", 16, spriteBatches.back()));
	UIText* spellOneStats = new UIText((int)(0.40f*m_screenWidth), 100, 1, fontBatches.back(), " ");
	m_model.setSpellStats(spellOneStats);
	p_overlayDrawables.push_back(spellOneStats);

	//Set attack 2 stats
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	fontBatches.emplace_back(new Solengine::Font("Fonts/Roboto-Regular.ttf", 16, spriteBatches.back()));
	UIText* spellTwoStats = new UIText((int)(0.40f*m_screenWidth), 80, 1, fontBatches.back(), " ");
	m_model.setSpellStats(spellTwoStats);
	p_overlayDrawables.push_back(spellTwoStats);

	//Set attack 3 stats
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	fontBatches.emplace_back(new Solengine::Font("Fonts/Roboto-Regular.ttf", 16, spriteBatches.back()));
	UIText* spellThreeStats = new UIText((int)(0.40f*m_screenWidth), 60, 1, fontBatches.back(), " ");
	m_model.setSpellStats(spellThreeStats);
	p_overlayDrawables.push_back(spellThreeStats);

	//Set attack 4 stats
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	fontBatches.emplace_back(new Solengine::Font("Fonts/Roboto-Regular.ttf", 16, spriteBatches.back()));
	UIText* spellFourStats = new UIText((int)(0.40f*m_screenWidth), 40, 1, fontBatches.back(), " ");
	m_model.setSpellStats(spellFourStats);
	p_overlayDrawables.push_back(spellFourStats);

	//Set current attack box
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	UIIcon* currentSpellBox = new UIIcon((int)(0.25f * m_screenWidth), 100, 100, 20, spriteBatches.back(), Solengine::ResourceManager::getTexture("Textures/zombie_pack/Panel.png").textureID);
	m_model.setSelectedSpellBox(currentSpellBox);
	p_overlayDrawables.push_back(currentSpellBox);


	//COMBAT LOG
	std::vector<UIText*> texts;
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	fontBatches.emplace_back(new Solengine::Font("Fonts/Roboto-Regular.ttf", 14, spriteBatches.back()));
	UIText* logLineOne = new UIText((int)(0.32f*m_screenWidth), 100, 1, fontBatches.back(), " ");
	texts.push_back(logLineOne);
	p_overlayDrawables.push_back(logLineOne);
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	fontBatches.emplace_back(new Solengine::Font("Fonts/Roboto-Regular.ttf", 14, spriteBatches.back()));
	UIText* logLineTwo = new UIText((int)(0.32f*m_screenWidth), 80, 1, fontBatches.back(), " ");
	texts.push_back(logLineTwo);
	p_overlayDrawables.push_back(logLineTwo);
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	fontBatches.emplace_back(new Solengine::Font("Fonts/Roboto-Regular.ttf", 14, spriteBatches.back()));
	UIText* logLineThree = new UIText((int)(0.32f*m_screenWidth), 60, 1, fontBatches.back(), " ");
	texts.push_back(logLineThree);
	p_overlayDrawables.push_back(logLineThree);
	spriteBatches.push_back(new Solengine::SpriteBatch());
	spriteBatches.back()->init();
	fontBatches.emplace_back(new Solengine::Font("Fonts/Roboto-Regular.ttf", 14, spriteBatches.back()));
	UIText* logLineFour = new UIText((int)(0.32f*m_screenWidth), 40, 1, fontBatches.back(), " ");
	texts.push_back(logLineFour);
	p_overlayDrawables.push_back(logLineFour);
	m_model.setCombatLog(texts);
}

//Game loop
void Scene::gameLoop()
{
	const float DESIRED_TICKS_PER_FRAME = 1000 / (float)m_fpsMax;
	static int pauseDuration = 0;
	//When initialised to true, this enables fps console announcing
	bool trackFPS = m_announceFPS;

	m_model.awake(p_units);

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

