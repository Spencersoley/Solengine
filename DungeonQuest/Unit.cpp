#include "Unit.h"

#include "Solengine/ResourceManager.h"

Unit::Unit() { p_SOL_S = new Solengine::SpriteSingle(); }

Unit::~Unit() { delete p_SOL_S; }

void Unit::init(glm::vec2 coords)
{
	m_pos.x = coords.x * TILE_WIDTH;
	m_pos.y = coords.y * TILE_WIDTH;

	m_colour = { 255, 255, 255, 255 };
	m_width = TILE_WIDTH;
	m_height = TILE_WIDTH;
	m_combatPointsMax = 5;
	m_combatPoints = m_combatPointsMax;
}

void Unit::death()
{
	m_delete = true;
	p_healthbar->m_delete = true;
	p_healthbarBackplate->m_delete = true;
}

void Unit::newTurn()
{
	m_turnPoints += 1;
	resetEnergy();
	resetCombatPoints();

	std::vector<Debuff*> erasors;

	//can we delete elements of a map by key whilst iterating through the map?w

	for (std::map<Debuff*, int>::iterator it = p_debuffs.begin(); it != p_debuffs.end(); it++)
	{
		modifyHealth(-(it->first->tick()));
		it->second--;
		if (it->second == 0)
			erasors.push_back(it->first);
	}

	for (size_t i = 0; i < erasors.size(); i++)
        p_debuffs.erase(erasors[i]);
}

void Unit::updateHealthbar()
{
	p_healthbar->resizeWidth((getHealth() * p_healthbarBackplate->getWidth()
		/ (float)getHealthMax()));
	p_healthbar->setPos({ getPos().x + 0.25 * TILE_WIDTH,
		getPos().y + 0.9 * TILE_WIDTH });
	p_healthbarBackplate->setPos({ getPos().x + 0.25 * TILE_WIDTH,
		getPos().y + 0.9 * TILE_WIDTH });
}
