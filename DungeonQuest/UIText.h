#pragma once

#include <Solengine/Font.h>

#include "UIElement.h"

class UIText : public UIElement
{
public:
	UIText() {};
	UIText(glm::vec2 v, int size, Solengine::Font* font, std::string msg,
		Solengine::ColourRGBA8 col = { 255, 255, 255, 255 });
	~UIText();

	void updateText(std::string tString) { m_trackedString = tString; }

	void draw();

	float m_duration;

	void activate(std::string txt, glm::ivec2 pos);
	bool updateEffect(float adjustedTicks);


protected:
	std::string m_message;

	std::string m_trackedString;

	Solengine::Font* p_SOL_spriteFont = nullptr;
};

