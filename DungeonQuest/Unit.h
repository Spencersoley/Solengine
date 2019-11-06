#pragma once

#include <glm/glm.hpp>

#include "Level.h"
#include "Drawable.h"
#include "MoveSet.h"
#include "UIIcon.h"
#include "StatusEffect.h"

const float AGENT_WIDTH = 64.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;


class Unit : public Drawable
{
public:
	Unit();
	virtual ~Unit();

	// GETTERS //
    glm::ivec2 GetCoords() const { return { floor(m_pos.x / TILE_WIDTH), floor(m_pos.y / TILE_WIDTH) }; }
	std::string GetName() const { return (m_name == "") ? "_" : m_name; }
	bool GetIsFriendly() const { return m_isFriendly; }
	int GetMoveCost() const { return m_movementCost; }
	int GetEnergy() const { return m_energy; }
	int GetEnergyMax() const { return m_energyMax; }
	int GetCombatPoints() const { return m_combatPoints; }
	int GetCombatPointsMax() const { return m_combatPointsMax; }
	int GetHealth() const  { return m_health; }
	int GetHealthMax()  const { return m_healthMax; }
	int GetSpeed() const { return m_speed; }
	int GetTurnPoints() const { return m_turnPoints; }
	MoveSet* GetMoveSet() { return &m_moveSet; }
	UIIcon* GetHB() { return p_healthbar; }
	UIIcon* GetHBB() { return p_healthbarBackplate; }

	// SETTERS //
	void SetEnergy(int nrg) { m_energy = nrg; }
	void ResetEnergy() { m_energy = m_energyMax; }
	void ResetCombatPoints() { m_combatPoints = m_combatPointsMax; }
	void RemoveEnergy(int energyUsed) { m_energy -= energyUsed; }
	void RemoveCombatPoints(int cbpUsed) { m_combatPoints -= cbpUsed; }
	void ModifyHealth(int dmg) { m_health += dmg; if (m_health > m_healthMax) m_health = m_healthMax; }
	void SetHealthbar(std::pair<UIIcon*, UIIcon*> h) { p_healthbar = h.first; p_healthbarBackplate = h.second; }

	void Init(glm::vec2 coords);

	void Death();

	void NewTurn();

	void UpdateHealthbar();

	std::map<StatusEffect*, int> GetStatusEffects() { return p_statusEffects; }

	void ApplyDebuff(StatusEffect* statusEffect)
	{
		p_statusEffects[statusEffect] += statusEffect->GetDuration();
	}

	bool HasDebuff(StatusEffect* statusEffect)
	{
		for (std::map<StatusEffect*, int>::iterator it = p_statusEffects.begin(); it != p_statusEffects.end(); it++)
			if (it->first->GetName() == statusEffect->GetName())
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