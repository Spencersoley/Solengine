#pragma once

#include "Drawable.h"

#include "Unit.h"

#include <vector>

extern const int TILE_WIDTH;

class EffectManager
{
public:
	EffectManager();
	~EffectManager();

	std::vector<Drawable*> getEffects() { return p_visualEffects; }

	void updateEffects(float adj);

	void newCombatEffect(Unit* tarUnit, Spell* spellCast);
	void newCombatEffect(Unit* tarUnit, std::map<Debuff*, int> activeDebuffs);


private:

	std::vector<Drawable*> p_visualEffects;
};
