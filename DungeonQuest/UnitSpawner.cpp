#include "UnitSpawner.h"

UnitSpawner::UnitSpawner() {}

UnitSpawner::~UnitSpawner() {}

void UnitSpawner::init(SpellBook* sb, std::vector<Level*> levels, int currentLevel)
{
	p_spellBook = sb;
	p_levels = levels;
	m_currentLevel = currentLevel;
}

Unit* UnitSpawner::spawnAdept()
{
	Unit* adept = new Adept(p_spellBook);
    adept->init(p_levels[m_currentLevel]->getAdeptSpawnCoords());

	adept->setHealthbar(createHealthbar());

	return adept;
}

Unit* UnitSpawner::spawnFighter()
{
	Unit* fighter = new Fighter(p_spellBook);
	fighter->init(p_levels[m_currentLevel]->getFighterSpawnCoords());

	fighter->setHealthbar(createHealthbar());

	return fighter;
}

Unit* UnitSpawner::spawnScout()
{
	Unit* scout = new Scout(p_spellBook);
	scout->init(p_levels[m_currentLevel]->getScoutSpawnCoords());

	scout->setHealthbar(createHealthbar());

	return scout;
}

Unit* UnitSpawner::spawnRat()
{
	Unit* rat = new Rat(p_spellBook);
	rat->init(p_levels[m_currentLevel]->getEnemySpawnCoords());

	rat->setHealthbar(createHealthbar());

	return rat;
}

Unit* UnitSpawner::spawnBat()
{
	Unit* bat = new Bat(p_spellBook);
	bat->init(p_levels[m_currentLevel]->getEnemySpawnCoords());

	bat->setHealthbar(createHealthbar());

	return bat;
}

Unit* UnitSpawner::spawnEnemy()
{
	int r = rand();
	if (r % 2 == 0) return spawnBat();
	else return spawnRat();
}

std::pair<UIIcon*, UIIcon*> UnitSpawner::createHealthbar()
{
	UIIcon* hb = new UIIcon({ 0, 0 }, 0.5f * TILE_WIDTH, 0.1f * TILE_WIDTH,
		Solengine::ResourceManager::getTexture("Textures/DQ_pack/DQtile.png").textureID,
		{ 0, 255, 0, 255 });
	UIIcon* hbb = new UIIcon({ 0, 0 }, 0.5f * TILE_WIDTH, 0.1f * TILE_WIDTH,
		Solengine::ResourceManager::getTexture("Textures/DQ_pack/DQtile.png").textureID,
		{ 222, 0, 0, 255 });

	return { hb, hbb };
}

std::vector<Drawable*> UnitSpawner::getDrawables(Unit* unit)
{
	std::vector<Drawable*> drawableVec;

	drawableVec.push_back(unit->getHBB());
	drawableVec.push_back(unit->getHB());
	drawableVec.push_back(unit);

	return drawableVec;
}