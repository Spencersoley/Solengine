#pragma once

#include <Solengine/Font.h>

#include "UIElement.h"

class UIText : public UIElement
{
public:
	UIText(int x, int y, int z, Solengine::Font* font, std::string msg,
		Solengine::ColourRGBA8 col = { 255, 255, 255, 255 });
	~UIText();

	void updateText(std::string tString) { m_trackedString = tString; }

	void draw();

private:
	std::string m_message;

	std::string m_trackedString;

	Solengine::Font* p_SOL_spriteFont = nullptr;
};

