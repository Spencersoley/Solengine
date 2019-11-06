#include "MoveSet.h"

MoveSet::MoveSet() {}

MoveSet::~MoveSet() {}

void MoveSet::Init(SpellBook* sb)
{
	for (int i = 0; i < SPELLS_MAX; i++)
		p_spells.push_back(sb->GetNullSpell());
}

//Index is important as we'll be adding functionality for replacing spells
void MoveSet::AddSpell(Spell* spell, int index)
{
	p_spells[index] = spell;
}

Spell* MoveSet::GetSpell(int index)
{ 
	return p_spells[index];
}