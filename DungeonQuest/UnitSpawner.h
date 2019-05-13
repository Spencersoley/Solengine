#pragma once

#include <vector>

#include "UnitCompendium.h"

class UnitSpawner
{
public:
	UnitSpawner();
	~UnitSpawner();

	void init(SpellBook* sb, std::vector<Level*> levels, int currentLevel);

	Unit* spawnAdept();
	Unit* spawnFighter();
	Unit* spawnScout();

	Unit* spawnRat();

	std::vector<Drawable*> getDrawables(Unit* unit);

private:
	SpellBook* p_spellBook;
	std::pair<UIIcon*, UIIcon*> createHealthbar();
	std::vector<Level*> p_levels;
	int m_currentLevel;
};

