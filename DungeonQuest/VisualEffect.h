#pragma once
#include "Drawable.h"

#include <iostream>

class VisualEffect 
{
public:
	VisualEffect();
	virtual ~VisualEffect();

	virtual void draw() = 0;

	virtual bool updateEffect(float adjustedDeltaTicks) = 0;
	virtual void activate(std::string txt, glm::ivec2 pos) = 0;

protected: 
	float m_duration = 0;
};

