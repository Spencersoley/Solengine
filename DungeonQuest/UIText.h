#pragma once

#include <Solengine/Font.h>

#include "Unit.h"
#include "UIElement.h"

class UIText : public UIElement
{
public:
	UIText(int x, int y, int z, Solengine::Font* spriteFont, std::string message, int tracked, std::string trackedString);
	~UIText();

	void draw();

	void updateText(int trackedInt, std::string trackedString);

private:
	std::string m_message;

	int m_trackedInt;
	std::string m_trackedString;

	Solengine::Font* p_SOL_spriteFont = nullptr;
};

