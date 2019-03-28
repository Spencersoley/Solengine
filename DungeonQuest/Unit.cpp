#include "Unit.h"

#include "Solengine/ResourceManager.h"

Unit::Unit(glm::vec2 coords) : m_health(20), m_energy(15), m_name("Adept")
{
	m_coords = coords;
	m_position.x = m_coords.x * TILE_WIDTH;
	m_position.y = m_coords.y * TILE_WIDTH;
}

Unit::~Unit()
{

}

void Unit::draw(Solengine::SpriteBatch& spriteBatch)
{
	//uses Solengine::ResourceManager to grab the textureID, passes it to the spriteBatch.
	static int textureID = Solengine::ResourceManager::getTexture("Textures/zombie_pack/adept.png").textureID;

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = m_position.x;
	destRect.y = m_position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;

	spriteBatch.draw(destRect, uvRect, textureID, 0.0f, m_colour);
}
