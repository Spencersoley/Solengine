#include "Rat.h"

#include "Solengine/ResourceManager.h"

Rat::Rat()
{
	m_isVisible = true;
	m_isFriendly = false;
	m_movementCost = 5;
	m_energy = 20;
	m_energyMax = 20;
	m_health = 20;
	m_healthMax = 20;
	m_name = "Rat";
	m_textureID = Solengine::ResourceManager::getTexture(
		          "Textures/zombie_pack/rat.png").textureID;
}

Rat::~Rat()
{
}
