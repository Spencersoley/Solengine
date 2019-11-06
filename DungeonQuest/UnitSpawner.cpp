#include "UnitSpawner.h"

UnitSpawner::UnitSpawner() {}

UnitSpawner::~UnitSpawner() {}

void UnitSpawner::Init(SpellBook* sb, std::vector<Level*> levels, int currentLevel)
{
	p_spellBook = sb;
	p_levels = levels;
	m_currentLevel = currentLevel;
}

Unit* UnitSpawner::SpawnAdept()
{
	Unit* adept = new Adept(p_spellBook);
    adept->Init(p_levels[m_currentLevel]->GetAdeptSpawnCoords());

	adept->SetHealthbar(createHealthbar());

	return adept;
}

Unit* UnitSpawner::SpawnFighter()
{
	Unit* fighter = new Fighter(p_spellBook);
	fighter->Init(p_levels[m_currentLevel]->GetFighterSpawnCoords());

	fighter->SetHealthbar(createHealthbar());

	return fighter;
}

Unit* UnitSpawner::SpawnScout()
{
	Unit* scout = new Scout(p_spellBook);
	scout->Init(p_levels[m_currentLevel]->GetScoutSpawnCoords());

	scout->SetHealthbar(createHealthbar());

	return scout;
}

Unit* UnitSpawner::SpawnRat()
{
	Unit* rat = new Rat(p_spellBook);
	rat->Init(p_levels[m_currentLevel]->GetEnemySpawnCoords());

	rat->SetHealthbar(createHealthbar());

	return rat;
}

Unit* UnitSpawner::SpawnBat()
{
	Unit* bat = new Bat(p_spellBook);
	bat->Init(p_levels[m_currentLevel]->GetEnemySpawnCoords());

	bat->SetHealthbar(createHealthbar());

	return bat;
}

Unit* UnitSpawner::SpawnEnemy()
{
	int r = rand();
	if (r % 2 == 0) return SpawnBat();
	else return SpawnRat();
}

std::vector<Drawable*> UnitSpawner::GetDrawables(Unit* unit)
{
	std::vector<Drawable*> drawableVec;

	drawableVec.push_back(unit->GetHBB());
	drawableVec.push_back(unit->GetHB());
	drawableVec.push_back(unit);

	return drawableVec;
}

std::pair<UIIcon*, UIIcon*> UnitSpawner::createHealthbar()
{
	UIIcon* hb = new UIIcon({ 0, 0 }, 0.5f * TILE_WIDTH, 0.1f * TILE_WIDTH,
		Solengine::ResourceManager::GetTexture("Textures/DQ_pack/DQtile.png").textureID,
		{ 0, 255, 0, 255 });
	UIIcon* hbb = new UIIcon({ 0, 0 }, 0.5f * TILE_WIDTH, 0.1f * TILE_WIDTH,
		Solengine::ResourceManager::GetTexture("Textures/DQ_pack/DQtile.png").textureID,
		{ 222, 0, 0, 255 });

	return { hb, hbb };
}