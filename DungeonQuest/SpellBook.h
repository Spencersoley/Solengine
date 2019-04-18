#pragma once

#include "Spell.h"

struct NullSpell : Spell
{
	NullSpell()
	{
		m_cost = 0;
	};
	~NullSpell() { };
};

struct Strike : Spell
{
	Strike() 
	{
		m_name = "Strike"; 
		m_range = 3;
		m_damage = 3;
		m_cost = 4;
	};
	~Strike() {};
};

struct Slash : Spell
{
	Slash()
	{
		m_name = "Slash";
		m_range = 1; 
		m_damage = 3;
		m_cost = 5;
	};
	~Slash() {  };
};

struct SpellBook
{
	SpellBook() {};
	~SpellBook() {};

	NullSpell* nullSpell() { return &m_nullSpell; }
	Strike* strike() { return &m_strike; }
	Slash* slash() { return &m_slash; }

	NullSpell m_nullSpell;
	Strike m_strike;
	Slash m_slash;

};

