#include "Scene.h"

#include "Solengine/ResourceManager.h"
#include "Solengine/SDLInitialiser.h"
//#include "Solengine/ErrorHandler.h"

#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>

#include "LoadingScreen.h"
#include "UnitSpawner.h"


//TODO:
// Limit basic camera movement
// Improve status effects
// Mouseover tooltip on spells
// Button functionality
// damage randomizer (crit handling etc)
// add pause screen
// LERP movement

//Debuff tick at start of turn
//Add debuffs to combat log
//Combat effect class
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
void Scene::Run()
{
	initSystems();
	gameLoop(&m_model, &m_view);
}

//Initialise SDL, glew, OpenGL, shaders, fps manager and level
void Scene::initSystems()
{
	Solengine::initialiseSDL();
	
	m_view.Init(&m_SOL_cam, &m_SOL_uiCam, m_screenWidth, m_screenHeight);

	LoadingScreen loadScreen(m_screenWidth, m_screenHeight, &m_view);

	m_model.Init(m_physicsSpeed, &m_SOL_cam, m_screenWidth, m_screenHeight);

	initScene();
}

//Initialise the game content
void Scene::initScene()
{
	m_spellBook.InitSpells();

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

	p_levels.push_back(new Level(m_SOL_tileLevelLoader.ParseLevelData("Levels/DQlevel1.txt")));
	worldDrawables.push_back(p_levels.back());

	m_model.SetTileMap(p_levels[0]->GetTileMap());

	//LAYER 1

	//Set walkable highlight
	UIIcon* walkableHighlight = new UIIcon({ 0, 0 }, TILE_WIDTH, TILE_WIDTH,
		Solengine::ResourceManager::GetTexture("Textures/DQ_pack/DQtile.png").textureID,
		{ 0, 150, 0, 150 });
	m_model.SetWalkableHighlight(walkableHighlight);
	worldDrawables.push_back(walkableHighlight);

	//Set hover highlight
	UIIcon* hoverHighlight = new UIIcon({ 0, 0 }, TILE_WIDTH, TILE_WIDTH,
		Solengine::ResourceManager::GetTexture("Textures/DQ_pack/Aim.png").textureID,
		{ 200, 200, 200, 100 });
	m_model.SetHoverHighlight(hoverHighlight);
	worldDrawables.push_back(hoverHighlight);

	//Selection box
	UIIcon* selectionBox = new UIIcon({ 0, 0 }, TILE_WIDTH, TILE_WIDTH,
		Solengine::ResourceManager::GetTexture("Textures/DQ_pack/selection.png").textureID);
	m_model.SetSelectionBox(selectionBox);
	worldDrawables.push_back(selectionBox);

	//Current unit box
	UIIcon* currentUnitBox = new UIIcon({ 0, 0 }, TILE_WIDTH, TILE_WIDTH,
		Solengine::ResourceManager::GetTexture("Textures/DQ_pack/selection.png").textureID);
	m_model.SetCurrentUnitBox(currentUnitBox);
	worldDrawables.push_back(currentUnitBox);

	//LAYER 2

	UnitSpawner unitSpawner;
	unitSpawner.Init(&m_spellBook, p_levels, m_currentLevel);
	std::vector<Drawable*> tempDraw;

	//ADEPT INIT
	p_units.push_back(unitSpawner.SpawnAdept());
	tempDraw = unitSpawner.GetDrawables(p_units.back());
	worldDrawables.insert(worldDrawables.end(), tempDraw.begin(), tempDraw.end());

	//FIGHTER INIT
	p_units.push_back(unitSpawner.SpawnFighter());
	tempDraw = unitSpawner.GetDrawables(p_units.back());
	worldDrawables.insert(worldDrawables.end(), tempDraw.begin(), tempDraw.end());

	//SCOUT INIT
	p_units.push_back(unitSpawner.SpawnScout());
	tempDraw = unitSpawner.GetDrawables(p_units.back());
	worldDrawables.insert(worldDrawables.end(), tempDraw.begin(), tempDraw.end());

	//ENEMY INIT
	int enemyCount = p_levels[m_currentLevel]->GetEnemyCount();
	for (int i = 0; i < enemyCount; i++)
	{
		p_units.push_back(unitSpawner.SpawnEnemy());
		tempDraw = unitSpawner.GetDrawables(p_units.back());
		worldDrawables.insert(worldDrawables.end(), tempDraw.begin(), tempDraw.end());
	}

	//LAYER 3 (Overlay)

	//Sets ui backplate
	overlayDrawables.push_back(new UIIcon({ 0.017f*sW, 0 }, sW, 0.25f*sH,
		Solengine::ResourceManager::GetTexture("Textures/DQ_pack/Backplate1.png").textureID,
		{ 200, 200, 200, 255 }));
	m_model.SetUIPanelHeight(overlayDrawables.back()->GetHeight() - 20);

	//Set combatlog scroll
	UIIcon* scrollIcon = new UIIcon({ 0.754f*sW, 0.055*sH }, 0.008f*sW, 0.14f*sH,
		Solengine::ResourceManager::GetTexture("Textures/DQ_pack/DQtile.png").textureID,
		col1);
	m_model.SetScrollIcon(scrollIcon);
	overlayDrawables.push_back(scrollIcon);

	//Set current icon
	UIIcon* currentUnitIcon = new UIIcon({ 0.02f*sW, 0.033f*sH }, 0.25*sH, 0.25*sH);
	m_model.SetCurrentUnitIcon(currentUnitIcon);
	overlayDrawables.push_back(currentUnitIcon);       //collect in vector

	//Set current name
	UIText* currentUnitNameText = new UIText({ 0.06f*sW, 0.033f*sH }, textSize,
		new Solengine::Font(font1, fontSize), "", col1);
	m_model.SetCurrentUnitNameText(currentUnitNameText);   //assign use
	overlayDrawables.push_back(currentUnitNameText);     //collect in vector

	//Set current health
	UIText* currentUnitHealth = new UIText({ 0.12f*sW, 0.166f*sH }, textSize,
		new Solengine::Font(font1, fontSize), "HP: ", col1);
	m_model.SetCurrentUnitHealthText(currentUnitHealth);
	overlayDrawables.push_back(currentUnitHealth);

	//Set current energy
	UIText* currentUnitEnergy = new UIText({ 0.12f*sW , 0.133f*sH }, textSize,
		new Solengine::Font(font1, fontSize), "NRG: ", col1);
	m_model.SetCurrentUnitEnergyText(currentUnitEnergy);
	overlayDrawables.push_back(currentUnitEnergy);

	//Set current speed
	UIText* currentUnitSpeed = new UIText({ 0.12f*sW, 0.1f*sH }, textSize,
		new Solengine::Font(font1, fontSize), "SPD: ", col1);
	m_model.SetCurrentUnitSpeedText(currentUnitSpeed);
	overlayDrawables.push_back(currentUnitSpeed);

	//Set current combatPoints 
	UIText* currentCombatPoints = new UIText({ 0.12f*sW, 0.0666f*sH }, textSize,
		new Solengine::Font(font1, fontSize), "CBP: ", col1);
	m_model.SetCurrentUnitCombatPointsText(currentCombatPoints);
	overlayDrawables.push_back(currentCombatPoints);

	//Set selected icon
	UIIcon* selectedUnitIcon = new UIIcon({ 0.75f*sW, 0.033f*sH }, 0.25*sH, 0.25*sH);
	m_model.SetSelectedUnitIcon(selectedUnitIcon);
	overlayDrawables.push_back(selectedUnitIcon);       //collect in vector

	//Set selected name
	UIText* selectedUnitNameText = new UIText({ 0.8f*sW, 0.033f*sH }, textSize,
		new Solengine::Font(font1, fontSize), "", col1);
	m_model.SetSelectedUnitNameText(selectedUnitNameText);
	overlayDrawables.push_back(selectedUnitNameText);     //collect in vector

	//Set selected health
	UIText* selectedUnitHealth = new UIText({ 0.87f*sW, 0.166f*sH }, textSize,
		new Solengine::Font(font1, fontSize), "HP: ", col1);
	m_model.SetSelectedHealthText(selectedUnitHealth);
	overlayDrawables.push_back(selectedUnitHealth);

	//Set selected energy
	UIText* selectedUnitEnergy = new UIText({ 0.87f*sW, 0.133f*sH }, textSize,
		new Solengine::Font(font1, fontSize), "NRG: ", col1);
	m_model.SetSelectedEnergyText(selectedUnitEnergy);
	overlayDrawables.push_back(selectedUnitEnergy); 

	//Set selected speed
	UIText* selectedUnitSpeed = new UIText({ 0.87f*sW, 0.1f*sH }, textSize,
		new Solengine::Font(font1, fontSize), "SPD: ", col1);
	m_model.SetSelectedUnitSpeedText(selectedUnitSpeed);
	overlayDrawables.push_back(selectedUnitSpeed);

	//Set selected combatPoints 
	UIText* selectedCombatPoints = new UIText({ 0.87f*sW, 0.0666f*sH }, textSize,
		new Solengine::Font(font1, fontSize), "CBP: ", col1);
	m_model.SetSelectedUnitCombatPointsText(selectedCombatPoints);
	overlayDrawables.push_back(selectedCombatPoints);

	//Set attack 1 
	UIText* spellOneText = new UIText({ 0.20f*sW, 0.166f*sH }, textSize,
		new Solengine::Font(font1, fontSize), " 1: ", col1);
	m_model.SetSpellText(spellOneText);
	overlayDrawables.push_back(spellOneText);

	//Set attack 2 text
	UIText* spellTwoText = new UIText({0.20f*sW, 0.133f*sH}, textSize,
		new Solengine::Font(font1, fontSize), " 2: ", col1);
	m_model.SetSpellText(spellTwoText);
	overlayDrawables.push_back(spellTwoText);

	//Set attack 3 text
	UIText* spellThreeText = new UIText({ 0.20f*sW, 0.1f*sH }, textSize,
		new Solengine::Font(font1, fontSize), " 3: ", col1);
	m_model.SetSpellText(spellThreeText);
	overlayDrawables.push_back(spellThreeText);

	//Set attack 4 text
	UIText* spellFourText = new UIText({ 0.20f*sW, 0.066f*sH }, textSize,
		new Solengine::Font(font1, fontSize), " 4: ", col1);
	m_model.SetSpellText(spellFourText);
	overlayDrawables.push_back(spellFourText);


	//Set current attack box
	UIIcon* selectedSpellBox = new UIIcon({0.23f * sW, 0.1666f*sH}, 0.1666f*sH, 0.0333f*sH,
		Solengine::ResourceManager::GetTexture("Textures/DQ_pack/Panel.png").textureID);
	m_model.SetSelectedSpellBox(selectedSpellBox);
	overlayDrawables.push_back(selectedSpellBox);

	//COMBAT LOG

	std::vector<Drawable*> logTexts = m_model.GetCombatLog()->init(sW, sH);
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

	model->Awake(p_units);

	while (gameState != Solengine::GameState::EXIT)
	{
		while (gameState == Solengine::GameState::PLAY)
		{
			gameState = model->Update(pauseDuration, p_units);

			if (m_model.DeleteCheck()) deleteEntity();

			view->Update(p_worldDrawables, model->GetEffects(), p_overlayDrawables);
			
			m_SOL_fpsManager.LimitFPS(trackFPS, (int)DESIRED_TICKS_PER_FRAME);
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

			for (size_t j = i; j < p_worldDrawables.size() - 1; j++)
				p_worldDrawables[j] = p_worldDrawables[j + 1];
			p_worldDrawables.pop_back();
			i--;
		}
}