#pragma once

#include <iostream>
#include <Solengine/Vertex.h>

#include "StatusEffect.h"

class Unit;

enum class SpellType{ ATTACK, HEAL };

class Spell
{
public:
	Spell();
	virtual ~Spell();

	std::string GetName() const { return m_name; }
	int GetRange() const { return m_range; }
	SpellType GetType() const { return m_spellType; }
	int GetDamage() const { return m_damage; }
	int GetCost() const { return m_cost; }
	int GetTextureID() const { return m_textureID; }
	Solengine::ColourRGBA8 GetColour() const { return m_colour; }

	void Cast(Unit* caster, Unit* target);

protected:
	std::string m_name;
	SpellType m_spellType;

	StatusEffect* p_statusEffect = nullptr;

	int m_range;
	int m_damage;
	int m_cost;
	Solengine::ColourRGBA8 m_colour;
	unsigned int m_textureID;
};

