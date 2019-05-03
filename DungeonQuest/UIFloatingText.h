#pragma once
#include "UIText.h"
#include "VisualEffect.h"

#include <iostream>

class UIFloatingText : public UIText, public VisualEffect
{
public:
	UIFloatingText(glm::vec2 v, int size, Solengine::Font* font, std::string msg,
		Solengine::ColourRGBA8 col = { 255, 255, 255, 255 });
	~UIFloatingText();

	float m_duration = 0; //in milisec

	void draw() { UIText::draw(); }

	void activate(std::string txt, glm::ivec2 pos)
	{
		Drawable::setPos(pos);
		updateText(txt);
		Drawable::setVisible(true);
		m_duration = 10;
	}

	bool updateEffect(float adjustedDeltaTicks)
	{
		Drawable::redraw();
		static int framesPassed = 0;
		if (m_duration > 0)
		{
			framesPassed++;
			m_duration -= adjustedDeltaTicks;

			if (framesPassed % 10 == 0) Drawable::movePos({ 0, 1 });      //We can stabilise the speed of effects. How should we do this?

			return true;
		}
		else return false;
	}
};