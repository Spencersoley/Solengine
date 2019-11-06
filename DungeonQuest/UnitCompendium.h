#pragma once
#include "Unit.h"

#include "Solengine/ResourceManager.h"

// Write a file reader containing all this information.

struct Adept : public Unit
{
	Adept(SpellBook* sb)
	{
		m_moveSet.Init(sb);
		p_spellBook = sb;
		m_isVisible = true;
		m_isFriendly = true;
		m_movementCost = 5;
		m_speed = 14;
		m_energy = 20;
		m_energyMax = 20;
		m_health = 20;
		m_healthMax = 20;
		m_name = "Adept";
		m_textureID = Solengine::ResourceManager::GetTexture(
			"Textures/DQ_pack/adept.png").textureID;
		m_moveSet.AddSpell(sb->GetEnflame(), 0);
		m_moveSet.AddSpell(sb->GetCurse(), 1);
		m_moveSet.AddSpell(sb->GetHealRay(), 2);
		m_moveSet.AddSpell(sb->GetReplenish(), 3);

	}
	~Adept() {};
};

struct Fighter : public Unit
{
    Fighter(SpellBook* sb)
	{
		m_moveSet.Init(sb);
		p_spellBook = sb;
		m_isVisible = true;
		m_isFriendly = true;
		m_movementCost = 5;
		m_speed = 12;
		m_energy = 20;
		m_energyMax = 20;
		m_health = 22;
		m_healthMax = 22;
		m_name = "Fighter";
		m_textureID = Solengine::ResourceManager::GetTexture(
			"Textures/DQ_pack/fighter.png").textureID;
		m_moveSet.AddSpell(sb->GetStrike(), 0);
		m_moveSet.AddSpell(sb->GetShank(), 1);
	}
	~Fighter() { };

};

struct Scout : public Unit
{
	Scout(SpellBook* sb)
	{
		m_moveSet.Init(sb);
		p_spellBook = sb;
		m_isVisible = true;
		m_isFriendly = true;
		m_movementCost = 5;
		m_speed = 8;
		m_energy = 20;
		m_energyMax = 20;
		m_health = 21;
		m_healthMax = 21;
		m_name = "Scout";
		m_textureID = Solengine::ResourceManager::GetTexture(
			"Textures/DQ_pack/scout.png").textureID;
		m_moveSet.AddSpell(sb->GetStrike(), 0);
		m_moveSet.AddSpell(sb->GetBowShot(), 1);
		m_moveSet.AddSpell(sb->GetClaw(), 2);
	}
	~Scout() {};
};

struct Rat : public Unit
{
	Rat(SpellBook* sb)
	{
		m_moveSet.Init(sb);
		p_spellBook = sb;
		m_isVisible = true;
		m_isFriendly = false;
		m_movementCost = 5;
		m_speed = 10;
		m_energy = 20;
		m_energyMax = 20;
		m_health = 60;
		m_healthMax = 60;
		m_name = "Rat";
		m_textureID = Solengine::ResourceManager::GetTexture(
			"Textures/DQ_pack/rat.png").textureID;
		m_moveSet.AddSpell(sb->GetClaw(), 0);

	}
	~Rat() {};
};

struct Bat : public Unit
{
	Bat(SpellBook* sb)
	{
		m_moveSet.Init(sb);
		p_spellBook = sb;
		m_isVisible = true;
		m_isFriendly = false;
		m_movementCost = 5;
		m_speed = 10;
		m_energy = 20;
		m_energyMax = 20;
		m_health = 40;
		m_healthMax = 40;
		m_name = "Rat";
		m_textureID = Solengine::ResourceManager::GetTexture(
			"Textures/DQ_pack/bat.png").textureID;
		m_moveSet.AddSpell(sb->GetClaw(), 0);

	}
	~Bat() {};
};


class UnitCompendium
{
public:
	UnitCompendium() {}
	~UnitCompendium() {}
};

