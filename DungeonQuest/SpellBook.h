#pragma once

#include "Spell.h"

#include "Solengine/ResourceManager.h"

struct NullSpell : Spell
{
	NullSpell() {};
	~NullSpell() {};

	void init()
	{
		m_cost = 0;	
	}
};

struct Strike : Spell
{
	Strike() {};
	~Strike() {};

	void init()
	{
		m_name = "Strike";
		m_range = 1;
		m_damage = 6;
		m_cost = 4;
		m_textureID = Solengine::ResourceManager::getTexture(
			"Textures/DQ_pack/icon_strike.png").textureID;
		m_colour = { 200, 155, 155, 255 };
	}
};

struct Claw : Spell
{
	Claw() {};
	~Claw() {};

	void init()
	{
		m_name = "Claw";
		m_range = 1;
		m_damage = 2;
		m_cost = 2;
		m_textureID = Solengine::ResourceManager::getTexture(
			"Textures/DQ_pack/icon_claw.png").textureID;
		m_colour = { 255, 0, 0, 255 };
	}
};

struct Enflame : Spell
{
	Enflame() {};
	~Enflame() {};

	void init() 
	{
		m_name = "Enflame";
		m_range = 3;
		m_damage = 3;
		m_cost = 5;
		m_textureID = Solengine::ResourceManager::getTexture(
			"Textures/DQ_pack/icon_flame.png").textureID;
		m_colour = { 255, 50, 0, 255 };
	}
};

struct SpellBook
{
	SpellBook() {};
	~SpellBook() {};

	NullSpell* nullSpell() { return &m_nullSpell; }
	Strike* strike() { return &m_strike; }
	Enflame* enflame() { return &m_enflame; }
	Claw* claw() { return &m_claw; }

	NullSpell m_nullSpell;
	Strike m_strike;
	Claw m_claw;
	Enflame m_enflame;


	void initSpells()
	{
		m_nullSpell.init();
		m_strike.init();
		m_claw.init();
		m_enflame.init();
	}

};

