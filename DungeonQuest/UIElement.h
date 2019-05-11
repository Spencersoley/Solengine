#pragma once

#include <Solengine/SpriteBatch.h>
#include <Solengine/ResourceManager.h>

#include "Drawable.h"

class UIElement : public Drawable
{
public:
	UIElement();
	virtual ~UIElement();

	float m_duration;

	int m_framesPassed = 0;

	bool checkMouseover(glm::vec2 mousePos);

	bool updateEffect(float adjustedTicks);
};

