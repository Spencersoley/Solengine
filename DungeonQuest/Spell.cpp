#include "Spell.h"
#include "Unit.h"

Spell::Spell() {}
Spell::~Spell() {}

void Spell::cast(Unit* caster, Unit* target)
{
	if (m_spellType == SpellType::ATTACK)
		target->modifyHealth(-m_damage);

	if (m_spellType == SpellType::HEAL)
		target->modifyHealth(m_damage);
   
	caster->removeCombatPoints(m_cost);
}
