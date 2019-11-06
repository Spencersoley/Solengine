#pragma once

#include "Drawable.h"

#include "Unit.h"

#include <vector>

extern const int TILE_WIDTH;

class VisualEffectManager
{
public:
	VisualEffectManager();
	~VisualEffectManager();

	std::vector<std::pair<Drawable*, Drawable*>> GetEffects() { return p_visualEffects; }

	void UpdateEffects(float adj);

	void NewCombatEffect(Unit* tarUnit, Spell* spellCast);
	void NewCombatEffect(Unit* tarUnit, std::map<StatusEffect*, int> activeStatusEffects);


private:
	std::vector<std::pair<Drawable*, Drawable*>> p_visualEffects;
};

