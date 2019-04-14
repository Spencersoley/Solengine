#pragma once

#include <Solengine/Font.h>

#include "Unit.h"
#include "UIElement.h"

class UIText : public UIElement
{
public:
	UIText(int x, int y, int z, Solengine::Font* spriteFont, std::string message);
	~UIText();

	void updateText(std::string trackedString) { m_trackedString = trackedString; }

	void draw();
	

private:
	std::string m_message;

	std::string m_trackedString;

	Solengine::Font* p_SOL_spriteFont = nullptr;
};

