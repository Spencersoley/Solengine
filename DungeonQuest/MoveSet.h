#pragma once

#include <iostream>

#include <vector>
#include "SpellBook.h"
#include "Spell.h"

const int SPELLS_MAX = 4;

class MoveSet
{
public:
	MoveSet();
	~MoveSet();

	void Init(SpellBook* sb);

	void AddSpell(Spell* s, int index);

	Spell* GetSpell(int index);
	size_t GetMoveSetSize() const { return p_spells.size(); }

	std::vector<Spell*> p_spells;	
};

