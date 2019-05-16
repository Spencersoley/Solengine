#pragma once

#include <Solengine/Font.h>

#include "UIElement.h"

class UIText : public UIElement
{
public:
	UIText() {};
	UIText(glm::vec2 v, float size, Solengine::Font* font, std::string msg,
		Solengine::ColourRGBA8 col = { 255, 255, 255, 255 });
	~UIText();

	void draw();

	void activate(std::string txt, glm::vec2 pos, float duration);

    void updateText(std::string tString) { m_trackedString = tString; }

protected:
	std::string m_message;

	std::string m_trackedString;

	Solengine::SpriteBatch* p_SOL_SB = nullptr;
	Solengine::Font* p_SOL_spriteFont = nullptr;
};

