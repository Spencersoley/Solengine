#include "FloatingDamageText.h"

#include <iostream>

FloatingDamageText::FloatingDamageText(glm::vec2 v, int size, 
	Solengine::Font* font, std::string msg, Solengine::ColourRGBA8 col)
{
    m_isVisible = true;
    m_pos = (glm::vec2)v;
    m_width = size;
    m_height = size;
    p_SOL_spriteFont = font;
    p_SOL_SB = font->getSpriteBatch();
    m_message = msg;
    m_colour = col;
}

FloatingDamageText::~FloatingDamageText()
{
}

void FloatingDamageText::activate(glm::ivec2 tarPos, std::string msg)
{
	setPos(tarPos);
	m_isVisible = true;
	m_lifeTime = 1.0f;
	updateText(msg);
}

void FloatingDamageText::update(float adjustedDeltaTicks)
{
	m_lifeTime -= adjustedDeltaTicks;
	movePos({ 0, 1 }); //upwards by 1
	if (m_lifeTime < 0) deactivate();
}

void FloatingDamageText::deactivate()
{
	setVisible();
	m_lifeTime = 0;
}

