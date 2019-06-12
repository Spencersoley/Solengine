#pragma once

#include "Spell.h"

#include "Solengine/ResourceManager.h"

struct Burn : StatusEffect
{
	Burn() {}
	~Burn() {}

	void init()
	{
		m_name = "Burn";
		m_statusType = StatusType::DEBUFF;
		m_damage = 1;
		m_duration = 3;
		m_textureID = Solengine::ResourceManager::getTexture(
			"Textures/DQ_pack/icon_flame.png").textureID;
		m_colour = { 255, 50, 0, 255 };
	}
};

struct Regen : StatusEffect
{
	Regen() {}
	~Regen() {}

	void init()
	{
		m_name = "Regen";
		m_statusType = StatusType::BUFF;
		m_damage = 1;
		m_duration = 3;
		m_textureID = Solengine::ResourceManager::getTexture(
			"Textures/DQ_pack/icon_flame.png").textureID;
		m_colour = { 63, 191, 89, 255 };
	}
};

struct StatusEffectBook
{
	StatusEffectBook() {};
	~StatusEffectBook() {};

	Burn* burn() { return &m_burn; }
	Regen* regen() { return &m_regen; }

	Burn m_burn;
	Regen m_regen;

	void initStatusEffects()
	{
		m_burn.init();
		m_regen.init();
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

	void init(StatusEffect* statusEffect)
	{
		m_name = "Enflame";
		m_spellType = SpellType::ATTACK;
		p_statusEffect = statusEffect;
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

struct Replenish : Spell
{
	Replenish() {}
	~Replenish() {};

	void init(StatusEffect* statusEffect)
	{
		m_name = "Replenish";
		m_spellType = SpellType::HEAL;
		p_statusEffect = statusEffect;
		m_range = 7;
		m_damage = 0;
		m_cost = 1;
		m_textureID = Solengine::ResourceManager::getTexture(
			"Textures/DQ_pack/icon_flame.png").textureID;
		m_colour = { 63, 191, 89, 255 };
	}
};

struct SpellBook
{
	SpellBook() {};
	~SpellBook() {};

	StatusEffectBook m_statusEffectBook;

	NullSpell* nullSpell() { return &m_nullSpell; }
	Strike* strike() { return &m_strike; }
	Shank* shank() { return &m_shank; }
	Enflame* enflame() { return &m_enflame; }
	Claw* claw() { return &m_claw; }
	Curse* curse() { return &m_curse; }
	BowShot* bowShot() { return &m_bowShot; }
	HealRay* healRay() { return &m_healRay; }
	Replenish* replenish() { return &m_replenish; }

	NullSpell m_nullSpell;
	Strike m_strike;
	Shank m_shank;
	Claw m_claw;
	Enflame m_enflame;
	Curse m_curse;
	BowShot m_bowShot;
	HealRay m_healRay;
	Replenish m_replenish;

	void initSpells()
	{
		m_statusEffectBook.initStatusEffects();

		m_nullSpell.init();
		m_strike.init();
		m_shank.init();
		m_claw.init();
		m_enflame.init(m_statusEffectBook.burn());
		m_replenish.init(m_statusEffectBook.regen());
		m_curse.init();
		m_bowShot.init();
		m_healRay.init();
	}
};













