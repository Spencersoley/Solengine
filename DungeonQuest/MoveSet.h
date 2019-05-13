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

	void init(SpellBook* sb);

	void addSpell(Spell* s, int index);

	Spell* getSpell(int index);
	size_t getMoveSetSize() const { return p_spells.size(); }

	std::vector<Spell*> p_spells;	
};

