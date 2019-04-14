#include "Fighter.h"

#include "Solengine/ResourceManager.h"

Fighter::Fighter() 
{
	m_isVisible = true;
	m_isFriendly = true;
	m_movementCost = 5;
	m_energy = 20;
	m_energyMax = 20;
	m_health = 22;
	m_healthMax = 22;
	m_name = "Fighter";
	m_textureID = Solengine::ResourceManager::getTexture(
		          "Textures/zombie_pack/fighter.png").textureID;
}

Fighter::~Fighter()
{
}

