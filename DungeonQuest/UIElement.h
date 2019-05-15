#pragma once

#include <Solengine/ResourceManager.h>

#include "Drawable.h"

class UIElement : public Drawable
{
public:
	UIElement();
	virtual ~UIElement();

	float m_duration;

	bool updateEffect(float adjustedTicks);
};

