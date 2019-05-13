#include "Unit.h"

#include "Solengine/ResourceManager.h"

Unit::Unit() {}

Unit::~Unit() {}

void Unit::init(glm::vec2 coords)
{
	m_pos.x = coords.x * TILE_WIDTH;
	m_pos.y = coords.y * TILE_WIDTH;

	m_colour = { 255, 255, 255, 255 };
	m_width = TILE_WIDTH;
	m_height = TILE_WIDTH;
}

void Unit::death()
{
	m_delete = true;
	p_healthbar->m_delete = true;
	p_healthbarBackplate->m_delete = true;
}

void Unit::newTurn()
{
	m_turnPoints += m_speed;
	m_energy = m_energyMax;
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
