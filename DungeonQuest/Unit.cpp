#include "Unit.h"

#include "Solengine/ResourceManager.h"

Unit::Unit(glm::vec2 coords, Solengine::SpriteBatch* spriteBatch) : m_health(20), m_energy(15), m_name("Adept")
{
	m_coords = coords;
	m_position.x = m_coords.x * TILE_WIDTH;
	m_position.y = m_coords.y * TILE_WIDTH;

	p_SOL_SB = spriteBatch;

	m_textureID = Solengine::ResourceManager::getTexture("Textures/zombie_pack/adept.png").textureID;
}

Unit::~Unit()
{
}

void Unit::draw()
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	static Solengine::ColourRGBA8 colour = { 255, 255, 255, 255 };

	glm::vec4 destRect;
	destRect.x = m_position.x;
	destRect.y = m_position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;

	p_SOL_SB->draw(destRect, uvRect, m_textureID, 0.0f, colour);
}
