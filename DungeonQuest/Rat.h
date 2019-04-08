#pragma once
#include "Unit.h"

class Rat :  public Unit
{
public:
	Rat();
	~Rat();

	void init(glm::vec2 coords, Solengine::SpriteBatch* spriteBatch);
};

