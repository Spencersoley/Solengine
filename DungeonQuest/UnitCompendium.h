#pragma once
#include "Unit.h"

#include "Solengine/ResourceManager.h"

struct Adept : public Unit
{
	Adept(SpellBook* sb)
	{
		m_moveSet.init(sb);
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
		m_textureID = Solengine::ResourceManager::getTexture(
			"Textures/DQ_pack/adept.png").textureID;
		m_moveSet.addSpell(sb->enflame(), 0);
		m_moveSet.addSpell(sb->curse(), 1);
		m_moveSet.addSpell(sb->healingRay(), 2);

	}
	~Adept() {};
};

struct Fighter : public Unit
{
    Fighter(SpellBook* sb)
	{
		m_moveSet.init(sb);
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
		m_textureID = Solengine::ResourceManager::getTexture(
			"Textures/DQ_pack/fighter.png").textureID;
		m_moveSet.addSpell(sb->strike(), 0);
	}
	~Fighter() { };

};

struct Scout : public Unit
{
	Scout(SpellBook* sb)
	{
		m_moveSet.init(sb);
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
		m_textureID = Solengine::ResourceManager::getTexture(
			"Textures/DQ_pack/scout.png").textureID;
		m_moveSet.addSpell(sb->strike(), 0);
		m_moveSet.addSpell(sb->bowShot(), 1);
		m_moveSet.addSpell(sb->claw(), 2);
	}
	~Scout() {};
};

struct Rat : public Unit
{
	Rat(SpellBook* sb)
	{
		m_moveSet.init(sb);
		p_spellBook = sb;
		m_isVisible = true;
		m_isFriendly = false;
		m_movementCost = 5;
		m_speed = 10;
		m_energy = 20;
		m_energyMax = 20;
		m_health = 20;
		m_healthMax = 20;
		m_name = "Rat";
		m_textureID = Solengine::ResourceManager::getTexture(
			"Textures/DQ_pack/rat.png").textureID;
		m_moveSet.addSpell(sb->claw(), 0);

	}
	~Rat() {};
};


class UnitCompendium
{
public:
	UnitCompendium() {}
	~UnitCompendium() {}
};

