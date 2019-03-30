#include "UIText.h"

#include <iostream>

UIText::UIText(int x, int y, int z, Solengine::Font* spriteFont, std::string message, Unit* currentUnit)
{
	m_xPos = x;
	m_yPos = y;
	m_width = z;
	m_height = z;
	p_SOL_spriteFont = spriteFont;
	p_SOL_SB = spriteFont->getSpriteBatch();

	m_message = message;
	p_currentUnit = currentUnit;
}

UIText::~UIText()
{
}

void UIText::draw()
{
	static Solengine::ColourRGBA8 colour = { 255, 255, 255, 255 };

	glm::vec2 pos = { m_xPos, m_yPos };
	glm::vec2 size = { m_width, m_height };

	//+ currentUnit->getName()).c_str()

	

	p_SOL_spriteFont->draw((m_message + p_currentUnit->getName()).c_str(), pos, size, 0.0f, colour);
}


void UIText::updateText()
{
	//p_currentUnit 
}