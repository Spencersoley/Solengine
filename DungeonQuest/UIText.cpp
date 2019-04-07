#include "UIText.h"

#include <iostream>

UIText::UIText(int x, int y, int z, Solengine::Font* spriteFont, std::string message, int trackedInt)
{
	m_xPos = x;
	m_yPos = y;
	m_width = z;
	m_height = z;
	p_SOL_spriteFont = spriteFont;
	p_SOL_SB = spriteFont->getSpriteBatch();

	m_message = message;

	m_trackedInt = trackedInt;
}

UIText::~UIText()
{
}

void UIText::draw()
{
	if (m_trackedString != "") 
	{
		static Solengine::ColourRGBA8 colour = { 255, 255, 255, 255 };

		glm::vec2 pos = { m_xPos, m_yPos };
		glm::vec2 size = { m_width, m_height };

		//+ currentUnit->getName()).c_str()

		if (m_trackedString == "")
		{
			p_SOL_spriteFont->draw((m_message + std::to_string(m_trackedInt)).c_str(), pos, size, 0.0f, colour);
		}
		else
		{
			p_SOL_spriteFont->draw((m_message + m_trackedString).c_str(), pos, size, 0.0f, colour);
		}
	}
}

void UIText::updateText(int trackedInt, std::string trackedString)
{
	m_trackedInt = trackedInt;
	m_trackedString = trackedString;
}