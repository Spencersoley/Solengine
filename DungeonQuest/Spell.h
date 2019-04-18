#pragma once

#include <iostream>

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

	void cast(Unit* caster, Unit* target);

protected:
	std::string m_name;
	int m_range;
	int m_damage;
	int m_cost;
};

