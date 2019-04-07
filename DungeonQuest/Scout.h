#pragma once

#include "Unit.h"

class Scout : public Unit
{
public:
	Scout();
	~Scout();

	void init(glm::vec2 coords, Solengine::SpriteBatch* spriteBatch);

};

