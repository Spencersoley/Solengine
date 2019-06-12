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

	if (p_statusEffect != nullptr && !target->hasDebuff(p_statusEffect))
	{
		target->applyDebuff(p_statusEffect);
	} 
	   
	caster->removeCombatPoints(m_cost);
}
