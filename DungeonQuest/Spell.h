#pragma once

#include <iostream>
#include <Solengine/Vertex.h>

#include "Debuff.h"

class Unit;

enum class SpellType{ ATTACK, HEAL };

class Spell
{
public:
	Spell();
	virtual ~Spell();

	std::string getName() const { return m_name; }
	int getRange() const { return m_range; }
	SpellType getType() const { return m_spellType; }
	int getDamage() const { return m_damage; }
	int getCost() const { return m_cost; }
	int getTextureID() const { return m_textureID; }
	Solengine::ColourRGBA8 getColour() const { return m_colour; }

	void cast(Unit* caster, Unit* target);

protected:
	std::string m_name;
	SpellType m_spellType;

	Debuff* p_debuff = nullptr; 

	int m_range;
	int m_damage;
	int m_cost;
	Solengine::ColourRGBA8 m_colour;
	unsigned int m_textureID;
};

