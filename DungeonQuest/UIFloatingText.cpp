#include "UIFloatingText.h"

UIFloatingText::UIFloatingText(glm::vec2 v, int size, Solengine::Font* font, std::string msg,
	Solengine::ColourRGBA8 col)
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

UIFloatingText::~UIFloatingText()
{
}
