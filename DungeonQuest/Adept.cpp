#include "Adept.h"

#include "Solengine/ResourceManager.h"

Adept::Adept(SpellBook* sb)
{
	m_moveSet.init(sb);
	p_spellBook = sb;
	m_isVisible = true;
	m_isFriendly = true;
	m_movementCost = 5;
	m_speed = 14;
	m_energy = 20;
	m_energyMax = 20;
	m_health = 20;
	m_healthMax = 20;
	m_name = "Adept";
	m_textureID = Solengine::ResourceManager::getTexture(
		"Textures/DQ_pack/adept.png").textureID;
	m_moveSet.addSpell(sb->enflame(), 0);

}

Adept::~Adept()
{
}



