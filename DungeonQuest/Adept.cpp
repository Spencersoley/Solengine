#include "Adept.h"

#include "Solengine/ResourceManager.h"

Adept::Adept()
{
	m_isFriendly = true;
	m_energy = 20;
	m_energyMax = 20;
	m_health = 20;
	m_healthMax = 20;
	m_name = "Adept";
}

Adept::~Adept()
{
}

void Adept::init(glm::vec2 coords, Solengine::SpriteBatch* spriteBatch)
{
	m_position.x = coords.x * TILE_WIDTH;
	m_position.y = coords.y * TILE_WIDTH;

	p_SOL_SB = spriteBatch;

	m_textureID = Solengine::ResourceManager::getTexture("Textures/zombie_pack/adept.png").textureID;
}

