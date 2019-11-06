#pragma once

#include <vector>

#include "UnitCompendium.h"

class UnitSpawner
{
public:
	UnitSpawner();
	~UnitSpawner();

	void Init(SpellBook* sb, std::vector<Level*> levels, int currentLevel);

	Unit* SpawnAdept();
	Unit* SpawnFighter();
	Unit* SpawnScout();

	Unit* SpawnRat();
	Unit* SpawnBat();

	Unit* SpawnEnemy();

	std::vector<Drawable*> GetDrawables(Unit* unit);

private:
	SpellBook* p_spellBook;
	std::pair<UIIcon*, UIIcon*> createHealthbar();
	std::vector<Level*> p_levels;
	int m_currentLevel;
};

