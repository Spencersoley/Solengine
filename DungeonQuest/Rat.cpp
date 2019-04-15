#include "Rat.h"

#include "Solengine/ResourceManager.h"

Rat::Rat(SpellBook* sb)
{
	m_moveSet.init(sb);
	p_spellBook = sb;
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
	m_moveSet.addSpell(sb->strike(), 0);

}

Rat::~Rat()
{
}
