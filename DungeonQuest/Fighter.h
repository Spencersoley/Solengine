#pragma once

#include "Unit.h"

class Fighter : public Unit
{
public:
	Fighter();
	~Fighter();

	void init(glm::vec2 coords, Solengine::SpriteBatch* spriteBatch);

};

