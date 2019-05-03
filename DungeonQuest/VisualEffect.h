#pragma once
#include "Drawable.h"

#include <iostream>

class VisualEffect : public Drawable 
{
public:
	VisualEffect();
	~VisualEffect();

	void draw() {}

	virtual bool updateEffect(float adjustedDeltaTicks) = 0;
	virtual void activate(std::string txt, glm::ivec2 pos) = 0;
};

