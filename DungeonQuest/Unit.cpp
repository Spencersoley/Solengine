#include "Unit.h"

#include "Solengine/ResourceManager.h"

Unit::Unit()
{
}

Unit::~Unit()
{
}

void Unit::init(glm::vec2 coords, Solengine::SpriteBatch* spriteBatch)
{
	m_pos.x = coords.x * TILE_WIDTH;
	m_pos.y = coords.y * TILE_WIDTH;

	m_colour = { 255, 255, 255, 255 };
	m_width = TILE_WIDTH;
	m_height = TILE_WIDTH;

	p_SOL_SB = spriteBatch;
}