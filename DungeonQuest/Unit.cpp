#include "Unit.h"

#include "Solengine/ResourceManager.h"

Unit::Unit() { p_SOL_S = new Solengine::SpriteSingle(); }

Unit::~Unit() { delete p_SOL_S; }

void Unit::Init(glm::vec2 coords)
{
	m_pos.x = coords.x * TILE_WIDTH;
	m_pos.y = coords.y * TILE_WIDTH;

	m_colour = { 255, 255, 255, 255 };
	m_width = TILE_WIDTH;
	m_height = TILE_WIDTH;
	m_combatPointsMax = 5;
	m_combatPoints = m_combatPointsMax;
}

void Unit::Death()
{
	m_delete = true;
	p_healthbar->m_delete = true;
	p_healthbarBackplate->m_delete = true;
}

void Unit::NewTurn()
{
	m_turnPoints += 1;
	ResetEnergy();
	ResetCombatPoints();

	std::vector<StatusEffect*> erasors;

	//can we delete elements of a map by key whilst iterating through the map?

	for (std::map<StatusEffect*, int>::iterator it = p_statusEffects.begin(); it != p_statusEffects.end(); it++)
	{
		if (it->first->m_statusType == StatusType::DEBUFF)
		    ModifyHealth(-(it->first->Tick()));
		if (it->first->m_statusType == StatusType::BUFF)
			ModifyHealth(+(it->first->Tick()));

		it->second--;
		if (it->second == 0)
			erasors.push_back(it->first);
	}

	for (size_t i = 0; i < erasors.size(); i++)
        p_statusEffects.erase(erasors[i]);
}

void Unit::UpdateHealthbar()
{
	p_healthbar->ResizeWidth((GetHealth() * p_healthbarBackplate->GetWidth()
		/ (float)GetHealthMax()));
	p_healthbar->SetPos({ GetPos().x + 0.25 * TILE_WIDTH,
		GetPos().y + 0.9 * TILE_WIDTH });
	p_healthbarBackplate->SetPos({ GetPos().x + 0.25 * TILE_WIDTH,
		GetPos().y + 0.9 * TILE_WIDTH });
}
