#include "Rat.h"

#include "Solengine/ResourceManager.h"

Rat::Rat()
{
	m_isFriendly = false;
	m_energy = 20;
	m_energyMax = 20;
	m_health = 20;
	m_healthMax = 20;
	m_name = "Rat";
}

Rat::~Rat()
{
}

void Rat::init(glm::vec2 coords, Solengine::SpriteBatch* spriteBatch)
{

	m_coords = coords;
	m_position.x = m_coords.x * TILE_WIDTH;
	m_position.y = m_coords.y * TILE_WIDTH;

	p_SOL_SB = spriteBatch;

	m_textureID = Solengine::ResourceManager::getTexture("Textures/zombie_pack/rat.png").textureID;
}

