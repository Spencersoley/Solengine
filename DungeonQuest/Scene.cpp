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
#include "LoadingScreen.h"


//TODO:
// Limit basic camera movement
// STatus effects etc
// Mouseover tooltip on spells

//Constructor will initialise private member variables
Scene::Scene() :
	m_screenWidth(1200), 
	m_screenHeight(600), 
	m_currentLevel(0),
	m_turnCounter(0),
	m_physicsSpeed(0.02f),
	m_fpsMax(600),
	m_announceFPS(false)
{
}

//Destructor
Scene::~Scene()
{
	for (size_t i = 0; i < p_worldDrawables.size(); i++)
		delete p_worldDrawables[i];
	
	for (size_t i = 0; i < p_overlayDrawables.size(); i++)
		delete p_overlayDrawables[i];
}

//Runs the game
void Scene::run()
{
	initSystems();
	gameLoop(&m_model, &m_view);
}

//Initialise SDL, glew, OpenGL, shaders, fps manager and level
void Scene::initSystems()
{
	Solengine::initialiseSDL();
	
	m_view.init(&m_SOL_cam, &m_SOL_uiCam, m_screenWidth, m_screenHeight);

	LoadingScreen loadScreen(m_screenWidth, m_screenHeight, &m_view);

	m_model.init(m_physicsSpeed, &m_SOL_cam, m_screenWidth, m_screenHeight);

	initScene();
}

//Initialise the game content
void Scene::initScene()
{
	m_spellBook.initSpells();

	std::vector<Drawable*> worldDrawables;
	std::vector<Drawable*> overlayDrawables;
	Solengine::ColourRGBA8 col1 = { 255, 155, 40, 255 };
	Solengine::ColourRGBA8 col2 = { 155, 155, 155, 255 };

	int sW = m_screenWidth;
	int sH = m_screenHeight;

	//const char* font1 = "Fonts/Px437_VGA_SquarePx.ttf"; @ 24
	const char* font1 = "Fonts/Px437_VGA_SquarePx.ttf";
	int fontSize = 32;
	float textSize = 0.8f;

	p_levels.push_back(new Level(m_SOL_tileLevelLoader.ParseLevelData("Levels/DQlevel1.txt"),
		new Solengine::SpriteBatch()));
	worldDrawables.push_back(p_levels.back());

	m_model.setTileMap(p_levels[0]->getTileMap());

	//LAYER 1

	//Set walkable highlight
	UIIcon* walkableHighlight = new UIIcon({ 0, 0 }, TILE_WIDTH, TILE_WIDTH,
		new Solengine::SpriteBatch(),
		Solengine::ResourceManager::getTexture("Textures/DQ_pack/DQtile.png").textureID,
		{ 0, 150, 0, 150 });
	m_model.setWalkableHighlight(walkableHighlight);
	worldDrawables.push_back(walkableHighlight);

	//Set hover highlight
	UIIcon* hoverHighlight = new UIIcon({ 0, 0 }, TILE_WIDTH, TILE_WIDTH,
		new Solengine::SpriteBatch(),
		Solengine::ResourceManager::getTexture("Textures/DQ_pack/Aim.png").textureID,
		{ 200, 200, 200, 100 });
	m_model.setHoverHighlight(hoverHighlight);
	worldDrawables.push_back(hoverHighlight);

	//Selection box
	UIIcon* selectionBox = new UIIcon({ 0, 0 }, TILE_WIDTH, TILE_WIDTH,
		new Solengine::SpriteBatch(),
		Solengine::ResourceManager::getTexture("Textures/DQ_pack/selection.png").textureID);
	m_model.setSelectionBox(selectionBox);
	worldDrawables.push_back(selectionBox);

	//Current unit box
	UIIcon* currentUnitBox = new UIIcon({ 0, 0 }, TILE_WIDTH, TILE_WIDTH,
		new Solengine::SpriteBatch(),
		Solengine::ResourceManager::getTexture("Textures/DQ_pack/selection.png").textureID);
	m_model.setCurrentUnitBox(currentUnitBox);
	worldDrawables.push_back(currentUnitBox);

	//LAYER 2

	//ADEPT INIT
	p_units.push_back(new Adept(&m_spellBook));
	p_units.back()->init(p_levels[m_currentLevel]->getAdeptSpawnCoords(), new Solengine::SpriteBatch());

	UIIcon* hb = new UIIcon({ 0, 0 }, 0.5f * TILE_WIDTH, 0.1f * TILE_WIDTH,
		new Solengine::SpriteBatch(),
		Solengine::ResourceManager::getTexture("Textures/DQ_pack/DQtile.png").textureID,
		{ 0, 255, 0, 255 });
	UIIcon* hbb = new UIIcon({ 0, 0 }, 0.5f * TILE_WIDTH, 0.1f * TILE_WIDTH,
		new Solengine::SpriteBatch(),
		Solengine::ResourceManager::getTexture("Textures/DQ_pack/DQtile.png").textureID,
		{ 222, 0, 0, 255 });
	p_units.back()->setHealthbar(hb, hbb);
	worldDrawables.push_back(hbb);
	worldDrawables.push_back(hb);
	worldDrawables.push_back(p_units.back());
	m_model.setCurrentUnit(p_units.back());


	//FIGHTER INIT
	p_units.push_back(new Fighter(&m_spellBook));
	p_units.back()->init(p_levels[m_currentLevel]->getFighterSpawnCoords(),
		new Solengine::SpriteBatch());

	hb = new UIIcon({ 0, 0 }, 0.5f * TILE_WIDTH, 0.1f * TILE_WIDTH,
		new Solengine::SpriteBatch(),
		Solengine::ResourceManager::getTexture("Textures/DQ_pack/DQtile.png").textureID,
		{ 0, 255, 0, 255 });
	hbb = new UIIcon({ 0, 0 }, 0.5f * TILE_WIDTH, 0.1f * TILE_WIDTH,
		new Solengine::SpriteBatch(),
		Solengine::ResourceManager::getTexture("Textures/DQ_pack/DQtile.png").textureID,
		{ 222, 0, 0, 255 });
	p_units.back()->setHealthbar(hb, hbb);
	worldDrawables.push_back(hbb);
	worldDrawables.push_back(hb);
	worldDrawables.push_back(p_units.back());
	m_model.setSelectedUnit(p_units.back());

	//SCOUT INIT
	p_units.push_back(new Scout(&m_spellBook));
	p_units.back()->init(p_levels[m_currentLevel]->getScoutSpawnCoords(),
		new Solengine::SpriteBatch());


	hb = new UIIcon({ 0, 0 }, 0.5f * TILE_WIDTH, 0.1f * TILE_WIDTH,
		new Solengine::SpriteBatch(),
		Solengine::ResourceManager::getTexture("Textures/DQ_pack/DQtile.png").textureID,
		{ 0, 255, 0, 255 });
	hbb = new UIIcon({ 0, 0 }, 0.5f * TILE_WIDTH, 0.1f * TILE_WIDTH,
		new Solengine::SpriteBatch(),
		Solengine::ResourceManager::getTexture("Textures/DQ_pack/DQtile.png").textureID,
		{ 222, 0, 0, 255 });
	p_units.back()->setHealthbar(hb, hbb);
	worldDrawables.push_back(hbb);
	worldDrawables.push_back(hb);
	worldDrawables.push_back(p_units.back());

	//ENEMY INIT

	for (int i = 0; i < p_levels[m_currentLevel]->getEnemyCount(); i++)
	{
		p_units.push_back(new Rat(&m_spellBook));

		p_units.back()->init(p_levels[m_currentLevel]->getEnemySpawnCoords(i),
			new Solengine::SpriteBatch());

		hb = new UIIcon({ 0, 0 }, 0.5f * TILE_WIDTH, 0.1f * TILE_WIDTH,
			new Solengine::SpriteBatch(),
			Solengine::ResourceManager::getTexture("Textures/DQ_pack/DQtile.png").textureID,
			{ 0, 255, 0, 255 });
		hbb = new UIIcon({ 0, 0 }, 0.5f * TILE_WIDTH, 0.1f * TILE_WIDTH,
			new Solengine::SpriteBatch(),
			Solengine::ResourceManager::getTexture("Textures/DQ_pack/DQtile.png").textureID,
			{ 222, 0, 0, 255 });

		p_units.back()->setHealthbar(hb, hbb);
		worldDrawables.push_back(hbb);
		worldDrawables.push_back(hb);
		worldDrawables.push_back(p_units.back());
	}

	//LAYER 3 (Overlay)

	//Sets ui backplate
	overlayDrawables.push_back(new UIIcon({ 0.017f*sW, 0 }, sW, 0.25f*sH,
		new Solengine::SpriteBatch(),
		Solengine::ResourceManager::getTexture("Textures/DQ_pack/Backplate1.png").textureID,
		{ 200, 200, 200, 255 }));

	//Set combatlog scroll
	UIIcon* scrollIcon = new UIIcon({ 0.754f*sW, 0.055*sH }, 0.008f*sW, 0.14f*sH,
		new Solengine::SpriteBatch(),
		Solengine::ResourceManager::getTexture("Textures/DQ_pack/DQtile.png").textureID,
		col1);
	m_model.setScrollIcon(scrollIcon);
	overlayDrawables.push_back(scrollIcon);

	//Set current icon
	UIIcon* currentUnitIcon = new UIIcon({ 0.02f*sW, 0.033f*sH }, 0.25*sH, 0.25*sH,
		new Solengine::SpriteBatch());
	m_model.setCurrentUnitIcon(currentUnitIcon);
	overlayDrawables.push_back(currentUnitIcon);       //collect in vector

	//Set current name
	UIText* currentUnitNameText = new UIText({ 0.06f*sW, 0.033f*sH }, textSize,
		new Solengine::Font(font1, fontSize, new Solengine::SpriteBatch()),
		"", col1);
	m_model.setCurrentUnitNameText(currentUnitNameText);   //assign use
	overlayDrawables.push_back(currentUnitNameText);     //collect in vector

	//Set current health
	UIText* currentUnitHealth = new UIText({ 0.12f*sW, 0.166f*sH }, textSize,
		new Solengine::Font(font1, fontSize, new Solengine::SpriteBatch()),
		"HP: ", col1);
	m_model.setCurrentUnitHealthText(currentUnitHealth);
	overlayDrawables.push_back(currentUnitHealth);

	//Set current energy
	UIText* currentUnitEnergy = new UIText({ 0.12f*sW , 0.133f*sH }, textSize,
		new Solengine::Font(font1, fontSize, new Solengine::SpriteBatch()),
		"NRG: ", col1);
	m_model.setCurrentUnitEnergyText(currentUnitEnergy);
	overlayDrawables.push_back(currentUnitEnergy);

	//Set current speed
	UIText* currentUnitSpeed = new UIText({ 0.12f*sW, 0.1f*sH }, textSize,
		new Solengine::Font(font1, fontSize, new Solengine::SpriteBatch()),
		"SPD: ", col1);
	m_model.setCurrentUnitSpeedText(currentUnitSpeed);
	overlayDrawables.push_back(currentUnitSpeed);

	//Set selected icon
	UIIcon* selectedUnitIcon = new UIIcon({ 0.75f*sW, 0.033f*sH }, 0.25*sH, 0.25*sH,
		new Solengine::SpriteBatch());
	m_model.setSelectedUnitIcon(selectedUnitIcon);
	overlayDrawables.push_back(selectedUnitIcon);       //collect in vector

	//Set selected name
	UIText* selectedUnitNameText = new UIText({ 0.8f*sW, 0.033f*sH }, textSize,
		new Solengine::Font(font1, fontSize, new Solengine::SpriteBatch()),
		"", col1);
	m_model.setSelectedUnitNameText(selectedUnitNameText);
	overlayDrawables.push_back(selectedUnitNameText);     //collect in vector

	//Set selected health
	UIText* selectedUnitHealth = new UIText({ 0.87f*sW, 0.166f*sH }, textSize,
		new Solengine::Font(font1, fontSize, new Solengine::SpriteBatch()),
		"HP: ", col1);
	m_model.setSelectedHealthText(selectedUnitHealth);
	overlayDrawables.push_back(selectedUnitHealth);

	//Set selected energy
	UIText* selectedUnitEnergy = new UIText({ 0.87f*sW, 0.133f*sH }, textSize,
		new Solengine::Font(font1, fontSize, new Solengine::SpriteBatch()),
		"NRG: ", col1);
	m_model.setSelectedEnergyText(selectedUnitEnergy);
	overlayDrawables.push_back(selectedUnitEnergy); 

	//Set selected speed
	UIText* selectedUnitSpeed = new UIText({ 0.87f*sW, 0.1f*sH }, textSize,
		new Solengine::Font(font1, fontSize, new Solengine::SpriteBatch()),
		"SPD: ", col1);
	m_model.setSelectedUnitSpeedText(selectedUnitSpeed);
	overlayDrawables.push_back(selectedUnitSpeed);

	//Set attack 1 
	UIText* spellOneText = new UIText({ 0.20f*sW, 0.166f*sH }, textSize,
		new Solengine::Font(font1, fontSize, new Solengine::SpriteBatch()),
		" 1: ", col1);
	m_model.setSpellText(spellOneText);
	overlayDrawables.push_back(spellOneText);

	//Set attack 2 text
	UIText* spellTwoText = new UIText({0.20f*sW, 0.133f*sH}, textSize,
		new Solengine::Font(font1, fontSize, new Solengine::SpriteBatch()),
		" 2: ", col1);
	m_model.setSpellText(spellTwoText);
	overlayDrawables.push_back(spellTwoText);

	//Set attack 3 text
	UIText* spellThreeText = new UIText({ 0.20f*sW, 0.1f*sH }, textSize,
		new Solengine::Font(font1, fontSize, new Solengine::SpriteBatch()),
		" 3: ", col1);
	m_model.setSpellText(spellThreeText);
	overlayDrawables.push_back(spellThreeText);

	//Set attack 4 text
	UIText* spellFourText = new UIText({ 0.20f*sW, 0.066f*sH }, textSize,
		new Solengine::Font(font1, fontSize, new Solengine::SpriteBatch()),
		" 4: ", col1);
	m_model.setSpellText(spellFourText);
	overlayDrawables.push_back(spellFourText);

	//Set attack 1 stats
	UIText* spellOneStats = new UIText({ 0.40f*sW, 0.166f*sH }, textSize,
		new Solengine::Font(font1, fontSize, new Solengine::SpriteBatch()),
		" ", col1);
	m_model.setSpellStats(spellOneStats);
	overlayDrawables.push_back(spellOneStats);

	//Set attack 2 stats
	UIText* spellTwoStats = new UIText({ 0.40f*sW, 0.133f*sH }, textSize,
		new Solengine::Font(font1, fontSize, new Solengine::SpriteBatch()),
		" ", col1);
	m_model.setSpellStats(spellTwoStats);
	overlayDrawables.push_back(spellTwoStats);

	//Set attack 3 stats
	UIText* spellThreeStats = new UIText({ 0.40f*sW, 0.1f*sH }, textSize,
		new Solengine::Font(font1, fontSize, new Solengine::SpriteBatch()),
		" ", col1);
	m_model.setSpellStats(spellThreeStats);
	overlayDrawables.push_back(spellThreeStats);

	//Set attack 4 stats
	UIText* spellFourStats = new UIText({ 0.40f*sW, 0.066f*sH }, textSize,
		new Solengine::Font(font1, fontSize, new Solengine::SpriteBatch()),
		" ", col1);
	m_model.setSpellStats(spellFourStats);
	overlayDrawables.push_back(spellFourStats);

	//Set current attack box

	UIIcon* currentSpellBox = new UIIcon({0.23f * sW, 0.1666f*sH}, 0.1666f*sH, 0.0333f*sH,
		new Solengine::SpriteBatch(),
		Solengine::ResourceManager::getTexture("Textures/DQ_pack/Panel.png").textureID);
	m_model.setSelectedSpellBox(currentSpellBox);
	overlayDrawables.push_back(currentSpellBox);

	//COMBAT LOG

	std::vector<Drawable*> logTexts = m_model.getCombatLog()->init(sW, sH);
    overlayDrawables.insert(overlayDrawables.end(), logTexts.begin(), logTexts.end());

	//////////////////////////////////

	p_worldDrawables = worldDrawables;
	p_overlayDrawables = overlayDrawables;
}

//Game loop
void Scene::gameLoop(Model* model, View* view)
{
	const float DESIRED_TICKS_PER_FRAME = 1000 / (float)m_fpsMax;
	static int pauseDuration = 0;
	//When initialised to true, this enables fps console announcing
	bool trackFPS = m_announceFPS;

	Solengine::GameState gameState = Solengine::GameState::PLAY;

	model->awake(p_units);

	while (gameState != Solengine::GameState::EXIT)
	{
		while (gameState == Solengine::GameState::PLAY)
		{
			gameState = model->update(pauseDuration, p_units);

			if (m_model.deleteCheck()) deleteEntity();

			view->update(p_worldDrawables, model->getEffects(), p_overlayDrawables);
			
			m_SOL_fpsManager.limitFPS(trackFPS, (int)DESIRED_TICKS_PER_FRAME);
			pauseDuration = 0;
		}
		
		/*
		int pauseClockStart = SDL_GetTicks();
		while (gameState == Solengine::GameState::PAUSE)
		{
			

		}
		
		pauseDuration = SDL_GetTicks() - pauseClockStart;
		*/
	}
}

void Scene::deleteEntity()
{
	for (size_t i = 0; i < p_units.size(); i++)
		if (p_units[i]->m_delete)
		{
			for (size_t j = i; j < p_units.size() - 1; j++)
				p_units[j] = p_units[j + 1];
			p_units.pop_back();
		}

	for (size_t i = 0; i < p_worldDrawables.size(); i++)
		if (p_worldDrawables[i]->m_delete)
		{
			delete p_worldDrawables[i];
			//since order is important here we can't just popback!
			for (size_t j = i; j < p_worldDrawables.size() - 1; j++)
				p_worldDrawables[j] = p_worldDrawables[j + 1];
			p_worldDrawables.pop_back();
			i--;
		}
}