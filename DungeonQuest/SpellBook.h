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
		m_spellType = SpellType::ATTACK;
		m_range = 1;
		m_damage = 8;
		m_cost = 2;
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
		m_spellType = SpellType::ATTACK;
		m_range = 1;
		m_damage = 3;
		m_cost = 1;
		m_textureID = Solengine::ResourceManager::getTexture(
			"Textures/DQ_pack/icon_claw.png").textureID;
		m_colour = { 255, 0, 0, 255 };
	}
};

struct BowShot : Spell
{
	BowShot() {};
	~BowShot() {};

	void init()
	{
		m_name = "Bow Shot";
		m_spellType = SpellType::ATTACK;
		m_range = 6;
		m_damage = 4;
		m_cost = 2;
		m_textureID = Solengine::ResourceManager::getTexture(
			"Textures/DQ_pack/icon_shoot.png").textureID;
		m_colour = { 200, 155, 155, 255 };
	}
};

struct Enflame : Spell
{
	Enflame() {};
	~Enflame() {};

	void init() 
	{
		m_name = "Enflame";
		m_spellType = SpellType::ATTACK;
		m_range = 6;
		m_damage = 2;
		m_cost = 1;
		m_textureID = Solengine::ResourceManager::getTexture(
			"Textures/DQ_pack/icon_flame.png").textureID;
		m_colour = { 255, 50, 0, 255 };
	}
};

struct Curse : Spell
{
	Curse() {};
	~Curse() {};

	void init()
	{
		m_name = "Curse";
		m_spellType = SpellType::ATTACK;
		m_range = 4;
		m_damage = 8;
		m_cost = 3;
		m_textureID = Solengine::ResourceManager::getTexture(
			"Textures/DQ_pack/icon_flame.png").textureID;
		m_colour = { 55, 50, 200, 255 };
	}
};

struct HealingRay : Spell
{
	HealingRay() {}
	~HealingRay() {};

	void init()
	{
		m_name = "Healing Ray";
		m_spellType = SpellType::HEAL;
		m_range = 4;
		m_damage = 5;
		m_cost = 3;
		m_textureID = Solengine::ResourceManager::getTexture(
			"Textures/DQ_pack/icon_flame.png").textureID;
		m_colour = { 150, 150, 0, 255 };
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
	Curse* curse() { return &m_curse; }
	BowShot* bowShot() { return &m_bowShot; }
	HealingRay* healingRay() { return &m_healingRay; }

	NullSpell m_nullSpell;
	Strike m_strike;
	Claw m_claw;
	Enflame m_enflame;
	Curse m_curse;
	BowShot m_bowShot;
	HealingRay m_healingRay;

	void initSpells()
	{
		m_nullSpell.init();
		m_strike.init();
		m_claw.init();
		m_enflame.init();
		m_curse.init();
		m_bowShot.init();
		m_healingRay.init();
	}
};

