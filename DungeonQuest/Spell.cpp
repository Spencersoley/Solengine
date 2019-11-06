#include "Spell.h"
#include "Unit.h"

Spell::Spell() {}
Spell::~Spell() {}

void Spell::Cast(Unit* caster, Unit* target)
{
	if (m_spellType == SpellType::ATTACK)
		target->ModifyHealth(-m_damage);

	if (m_spellType == SpellType::HEAL)
		target->ModifyHealth(m_damage);

	if (p_statusEffect != nullptr && !target->HasDebuff(p_statusEffect))
	{
		target->ApplyDebuff(p_statusEffect);
	} 
	   
	caster->RemoveCombatPoints(m_cost);
}
