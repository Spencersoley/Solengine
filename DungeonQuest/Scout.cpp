#include "Scout.h"

#include "Solengine/ResourceManager.h"

Scout::Scout()
{
	m_isVisible = true;
	m_isFriendly = true;
	m_energy = 20;
	m_energyMax = 20;
	m_health = 21;
	m_healthMax = 21;
	m_name = "Scout";
	m_textureID = Solengine::ResourceManager::getTexture("Textures/zombie_pack/scout.png").textureID;
}

Scout::~Scout()
{
}
