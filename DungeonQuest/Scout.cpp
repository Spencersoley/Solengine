#include "Scout.h"

#include "Solengine/ResourceManager.h"

Scout::Scout(SpellBook* sb)
{
	m_moveSet.init(sb);
	p_spellBook = sb;
	m_isVisible = true;
	m_isFriendly = true;
	m_movementCost = 5;
	m_speed = 8;
	m_energy = 20;
	m_energyMax = 20;
	m_health = 21;
	m_healthMax = 21;
	m_name = "Scout";
	m_textureID = Solengine::ResourceManager::getTexture(
		          "Textures/zombie_pack/scout.png").textureID;
	m_moveSet.addSpell(sb->strike(), 0);
}

Scout::~Scout()
{
}
