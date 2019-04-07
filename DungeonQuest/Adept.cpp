#include "Adept.h"

#include "Solengine/ResourceManager.h"

Adept::Adept()
{
}

Adept::~Adept()
{
}

void Adept::init(glm::vec2 coords, Solengine::SpriteBatch* spriteBatch)
{
	m_energy = 20;
	m_health = 20;
	m_name = "Adept";

	m_coords = coords;
	m_position.x = m_coords.x * TILE_WIDTH;
	m_position.y = m_coords.y * TILE_WIDTH;

	p_SOL_SB = spriteBatch;

	m_textureID = Solengine::ResourceManager::getTexture("Textures/zombie_pack/adept.png").textureID;
}

