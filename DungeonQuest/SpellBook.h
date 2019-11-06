#pragma once

#include "Spell.h"

#include "Solengine/ResourceManager.h"

struct Burn : StatusEffect
{
	Burn() {}
	~Burn() {}

	void Init()
	{
		m_name = "Burn";
		m_statusType = StatusType::DEBUFF;
		m_damage = 1;
		m_duration = 3;
		m_textureID = Solengine::ResourceManager::GetTexture(
			"Textures/DQ_pack/icon_flame.png").textureID;
		m_colour = { 255, 50, 0, 255 };
	}
};

struct Regen : StatusEffect
{
	Regen() {}
	~Regen() {}

	void Init()
	{
		m_name = "Regen";
		m_statusType = StatusType::BUFF;
		m_damage = 1;
		m_duration = 3;
		m_textureID = Solengine::ResourceManager::GetTexture(
			"Textures/DQ_pack/icon_flame.png").textureID;
		m_colour = { 63, 191, 89, 255 };
	}
};

struct StatusEffectBook
{
	StatusEffectBook() {};
	~StatusEffectBook() {};

	Burn* GetBurn() { return &m_burn; }
	Regen* GetRegen() { return &m_regen; }

	Burn m_burn;
	Regen m_regen;

	void initStatusEffects()
	{
		m_burn.Init();
		m_regen.Init();
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

	void Init()
	{
		m_name = "Strike";
		m_spellType = SpellType::ATTACK;
		m_range = 1;
		m_damage = 8;
		m_cost = 2;
		m_textureID = Solengine::ResourceManager::GetTexture(
			"Textures/DQ_pack/icon_strike.png").textureID;
		m_colour = { 200, 155, 155, 255 };
	}
};

struct Shank : Spell
{
	Shank() {};
	~Shank() {};

	void Init()
	{
		m_name = "Shank";
		m_spellType = SpellType::ATTACK;
		m_range = 2;
		m_damage = 2;
		m_cost = 1;
		m_textureID = Solengine::ResourceManager::GetTexture(
			"Textures/DQ_pack/icon_strike.png").textureID;
		m_colour = { 100, 80, 80, 255 };
	}
};

struct Claw : Spell
{
	Claw() {};
	~Claw() {};

	void Init()
	{
		m_name = "Claw";
		m_spellType = SpellType::ATTACK;
		m_range = 1;
		m_damage = 3;
		m_cost = 1;
		m_textureID = Solengine::ResourceManager::GetTexture(
			"Textures/DQ_pack/icon_claw.png").textureID;
		m_colour = { 255, 0, 0, 255 };
	}
};

struct BowShot : Spell
{
	BowShot() {};
	~BowShot() {};

	void Init()
	{
		m_name = "Bow Shot";
		m_spellType = SpellType::ATTACK;
		m_range = 6;
		m_damage = 5;
		m_cost = 2;
		m_textureID = Solengine::ResourceManager::GetTexture(
			"Textures/DQ_pack/icon_shoot.png").textureID;
		m_colour = { 200, 155, 155, 255 };
	}
};

struct Enflame : Spell
{
	Enflame() {};
	~Enflame() {};

	void Init(StatusEffect* statusEffect)
	{
		m_name = "Enflame";
		m_spellType = SpellType::ATTACK;
		p_statusEffect = statusEffect;
		m_range = 6;
		m_damage = 2;
		m_cost = 1;
		m_textureID = Solengine::ResourceManager::GetTexture(
			"Textures/DQ_pack/icon_flame.png").textureID;
		m_colour = { 255, 50, 0, 255 };
	}
};

struct Curse : Spell
{
	Curse() {};
	~Curse() {};

	void Init()
	{
		m_name = "Curse";
		m_spellType = SpellType::ATTACK;
		m_range = 4;
		m_damage = 8;
		m_cost = 3;
		m_textureID = Solengine::ResourceManager::GetTexture(
			"Textures/DQ_pack/icon_flame.png").textureID;
		m_colour = { 55, 50, 200, 255 };
	}
};

struct HealRay : Spell
{
	HealRay() {}
	~HealRay() {};

	void Init()
	{
		m_name = "Heal Ray";
		m_spellType = SpellType::HEAL;
		m_range = 4;
		m_damage = 5;
		m_cost = 2;
		m_textureID = Solengine::ResourceManager::GetTexture(
			"Textures/DQ_pack/icon_flame.png").textureID;
		m_colour = { 150, 150, 0, 255 };
	}
};

struct Replenish : Spell
{
	Replenish() {}
	~Replenish() {};

	void Init(StatusEffect* statusEffect)
	{
		m_name = "Replenish";
		m_spellType = SpellType::HEAL;
		p_statusEffect = statusEffect;
		m_range = 7;
		m_damage = 0;
		m_cost = 1;
		m_textureID = Solengine::ResourceManager::GetTexture(
			"Textures/DQ_pack/icon_flame.png").textureID;
		m_colour = { 63, 191, 89, 255 };
	}
};

struct SpellBook
{
	SpellBook() {};
	~SpellBook() {};

	StatusEffectBook m_statusEffectBook;

	NullSpell* GetNullSpell() { return &m_nullSpell; }
	Strike* GetStrike() { return &m_strike; }
	Shank* GetShank() { return &m_shank; }
	Enflame* GetEnflame() { return &m_enflame; }
	Claw* GetClaw() { return &m_claw; }
	Curse* GetCurse() { return &m_curse; }
	BowShot* GetBowShot() { return &m_bowShot; }
	HealRay* GetHealRay() { return &m_healRay; }
	Replenish* GetReplenish() { return &m_replenish; }

	NullSpell m_nullSpell;
	Strike m_strike;
	Shank m_shank;
	Claw m_claw;
	Enflame m_enflame;
	Curse m_curse;
	BowShot m_bowShot;
	HealRay m_healRay;
	Replenish m_replenish;

	void InitSpells()
	{
		m_statusEffectBook.initStatusEffects();

		m_nullSpell.init();
		m_strike.Init();
		m_shank.Init();
		m_claw.Init();
		m_enflame.Init(m_statusEffectBook.GetBurn());
		m_replenish.Init(m_statusEffectBook.GetRegen());
		m_curse.Init();
		m_bowShot.Init();
		m_healRay.Init();
	}
};













