#pragma once

#include <iostream>
#include <Solengine/Vertex.h>

class Unit;

class Spell
{
public:
	Spell();
	virtual ~Spell();

	std::string getName() { return m_name; }
	
	int getRange() { return m_range; }
	int getDamage() { return m_damage; }
	int getCost() { return m_cost; }
	int getTextureID() { return m_textureID; }
	Solengine::ColourRGBA8 getColour() { return m_colour; }

	void cast(Unit* caster, Unit* target);

protected:
	std::string m_name;
	int m_range;
	int m_damage;
	int m_cost;
	Solengine::ColourRGBA8 m_colour;
	unsigned int m_textureID;
};

