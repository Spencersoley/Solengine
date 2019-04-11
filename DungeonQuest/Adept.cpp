#include "Adept.h"

#include "Solengine/ResourceManager.h"

Adept::Adept()
{
	m_isVisible = true;
	m_isFriendly = true;
	m_energy = 20;
	m_energyMax = 20;
	m_health = 20;
	m_healthMax = 20;
	m_name = "Adept";
	m_textureID = Solengine::ResourceManager::getTexture("Textures/zombie_pack/adept.png").textureID;
}

Adept::~Adept()
{
}



