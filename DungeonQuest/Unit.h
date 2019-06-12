#pragma once

#include <glm/glm.hpp>

#include "Level.h"
#include "Drawable.h"
#include "MoveSet.h"
#include "UIIcon.h"
#include "StatusEffect.h"
#include "EffectManager.h"

const float AGENT_WIDTH = 64.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;


class Unit : public Drawable
{
public:
	Unit();
	virtual ~Unit();

	// GETTERS //
    glm::ivec2 getCoords() const { return { floor(m_pos.x / TILE_WIDTH), floor(m_pos.y / TILE_WIDTH) }; }
	std::string getName() const { return (m_name == "") ? "_" : m_name; }
	bool getIsFriendly() const { return m_isFriendly; }
	int getMoveCost() const { return m_movementCost; }
	int getEnergy() const { return m_energy; }
	int getEnergyMax() const { return m_energyMax; }
	int getCombatPoints() const { return m_combatPoints; }
	int getCombatPointsMax() const { return m_combatPointsMax; }
	int getHealth() const  { return m_health; }
	int getHealthMax()  const { return m_healthMax; }
	int getSpeed() const { return m_speed; }
	int getTurnPoints() const { return m_turnPoints; }
	MoveSet* getMoveSet() { return &m_moveSet; }
	UIIcon* getHB() { return p_healthbar; }
	UIIcon* getHBB() { return p_healthbarBackplate; }

	// SETTERS //
	void setEnergy(int nrg) { m_energy = nrg; }
	void resetEnergy() { m_energy = m_energyMax; }
	void resetCombatPoints() { m_combatPoints = m_combatPointsMax; }
	void removeEnergy(int energyUsed) { m_energy -= energyUsed; }
	void removeCombatPoints(int cbpUsed) { m_combatPoints -= cbpUsed; }
	void modifyHealth(int dmg) { m_health += dmg; if (m_health > m_healthMax) m_health = m_healthMax; }
	void setHealthbar(std::pair<UIIcon*, UIIcon*> h) { p_healthbar = h.first; p_healthbarBackplate = h.second; }

	void init(glm::vec2 coords);

	void death();

	void newTurn();

	void updateHealthbar();

	std::map<StatusEffect*, int> getStatusEffects() { return p_statusEffects; }

	void applyDebuff(StatusEffect* statusEffect)
	{
		p_statusEffects[statusEffect] += statusEffect->getDuration();
	}

	bool hasDebuff(StatusEffect* statusEffect)
	{
		for (std::map<StatusEffect*, int>::iterator it = p_statusEffects.begin(); it != p_statusEffects.end(); it++)
			if (it->first->getName() == statusEffect->getName())
				return true;
		
		return false;
	}

protected:

	MoveSet m_moveSet;

	std::map<StatusEffect*, int> p_statusEffects;

	SpellBook* p_spellBook;
	UIIcon* p_healthbar = nullptr;
	UIIcon* p_healthbarBackplate = nullptr;

	int m_movementCost;
	int m_energy;
	int m_energyMax;
	int m_combatPoints;
	int m_combatPointsMax;
	int m_health;
	int m_healthMax;
	int m_speed;

	int m_turnPoints;
	bool m_isFriendly;
	std::string m_name;
};