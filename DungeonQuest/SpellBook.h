#pragma once

#include "Spell.h"

#include "Solengine/ResourceManager.h"


struct Burn : Debuff
{
	Burn() {}
	~Burn() {}

	void init()
	{
		m_name = "Burn";
		m_damage = 1;
		m_duration = 3;
		m_textureID = Solengine::ResourceManager::getTexture(
			"Textures/DQ_pack/icon_flame.png").textureID;
		m_colour = { 255, 50, 0, 255 };
	}
};

struct DebuffBook
{
	DebuffBook() {};
	~DebuffBook() {};

	Burn* burn() { return &m_burn; }

	Burn m_burn;

	void initDebuffs()
	{
		m_burn.init();
	}

};


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

struct Shank : Spell
{
	Shank() {};
	~Shank() {};

	void init()
	{
		m_name = "Shank";
		m_spellType = SpellType::ATTACK;
		m_range = 2;
		m_damage = 2;
		m_cost = 1;
		m_textureID = Solengine::ResourceManager::getTexture(
			"Textures/DQ_pack/icon_strike.png").textureID;
		m_colour = { 100, 80, 80, 255 };
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
		m_damage = 5;
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

	void init(Debuff* debuff)
	{
		m_name = "Enflame";
		m_spellType = SpellType::ATTACK;
		p_debuff = debuff;
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

struct HealRay : Spell
{
	HealRay() {}
	~HealRay() {};

	void init()
	{
		m_name = "Heal Ray";
		m_spellType = SpellType::HEAL;
		m_range = 4;
		m_damage = 5;
		m_cost = 2;
		m_textureID = Solengine::ResourceManager::getTexture(
			"Textures/DQ_pack/icon_flame.png").textureID;
		m_colour = { 150, 150, 0, 255 };
	}
};

struct SpellBook
{
	SpellBook() {};
	~SpellBook() {};

	DebuffBook m_debuffBook;

	NullSpell* nullSpell() { return &m_nullSpell; }
	Strike* strike() { return &m_strike; }
	Shank* shank() { return &m_shank; }
	Enflame* enflame() { return &m_enflame; }
	Claw* claw() { return &m_claw; }
	Curse* curse() { return &m_curse; }
	BowShot* bowShot() { return &m_bowShot; }
	HealRay* healRay() { return &m_healRay; }

	NullSpell m_nullSpell;
	Strike m_strike;
	Shank m_shank;
	Claw m_claw;
	Enflame m_enflame;
	Curse m_curse;
	BowShot m_bowShot;
	HealRay m_healRay;

	void initSpells()
	{
		m_debuffBook.initDebuffs();

		m_nullSpell.init();
		m_strike.init();
		m_shank.init();
		m_claw.init();
		m_enflame.init(m_debuffBook.burn());
		m_curse.init();
		m_bowShot.init();
		m_healRay.init();
	}
};













