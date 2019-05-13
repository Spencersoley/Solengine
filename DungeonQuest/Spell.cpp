#include "Spell.h"
#include "Unit.h"

Spell::Spell() {}

Spell::~Spell() {}

void Spell::cast(Unit* caster, Unit* target)
{
   target->removeHealth(m_damage);
   caster->removeEnergy(m_cost);
}
