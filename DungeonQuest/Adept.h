#pragma once
#include "Unit.h"

class Adept : public Unit
{
public:
	Adept();
	~Adept();

	void init(glm::vec2 coords, Solengine::SpriteBatch* spriteBatch);
};

