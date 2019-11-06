#pragma once

#include <Solengine/ResourceManager.h>

#include "Drawable.h"

class UIElement : public Drawable
{
public:
	UIElement();
	virtual ~UIElement();

	bool UpdateEffect(float adjustedTicks);

	float m_duration;
};

