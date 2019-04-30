#pragma once
#include "UIText.h"

#include <iostream>

class UIFloatingText : public UIText
{
public:
	UIFloatingText(glm::vec2 v, int size, Solengine::Font* font, std::string msg,
		Solengine::ColourRGBA8 col = { 255, 255, 255, 255 });
	~UIFloatingText();

	float m_duration = 0; //in milisec
	
	void activate(std::string txt, glm::ivec2 pos)
	{
		setPos(pos);
		updateText(txt);
		setVisible(true);
		m_duration = 10;
	}

	void update(float adjustedDeltaTicks)
	{
		static int framesPassed = 0;
		if (m_duration > 0) 
		{
			framesPassed++;
			m_duration -= adjustedDeltaTicks;
			std::cout << m_duration << std::endl;
			
			if (framesPassed % 10 == 0) movePos({ 0, 1 });
		}
		else
		{
			deactivate();
			framesPassed = 0;
		}
	}

	void deactivate()
	{
		updateText(" ");
		setVisible(false);
		
	}
};

