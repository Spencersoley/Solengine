#include "UIText.h"

#include <iostream>

UIText::UIText(int x, int y, int z, Solengine::Font* spriteFont, std::string message)
{
	m_xPos = x;
	m_yPos = y;
	m_width = z;
	m_height = z;
	p_SOL_spriteFont = spriteFont;
	p_SOL_SB = spriteFont->getSpriteBatch();

	m_message = message;
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


	    p_SOL_spriteFont->draw((m_message + m_trackedString).c_str(), pos, size, 0.0f, colour);
		
	}
}

void UIText::updateText(std::string trackedString)
{
	m_trackedString = trackedString;
}