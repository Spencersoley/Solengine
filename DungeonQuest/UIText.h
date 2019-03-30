#pragma once

#include <Solengine/Font.h>

#include "Unit.h"
#include "UIElement.h"

class UIText : public UIElement
{
public:
	UIText(int x, int y, int z, Solengine::Font* spriteFont, std::string message, Unit* currentUnit);
	~UIText();

	void draw();

	void updateText();

private:
	std::string m_message;

	Unit* p_currentUnit;

	Solengine::Font* p_SOL_spriteFont = nullptr;
};

