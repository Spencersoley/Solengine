#include "UIFloatingText.h"

UIFloatingText::UIFloatingText(glm::vec2 v, int size, Solengine::Font* font, std::string msg,
	Solengine::ColourRGBA8 col)
{
	Drawable::m_isVisible = true;
	Drawable::m_pos = (glm::vec2)v;
	Drawable::m_width = size;
	Drawable::m_height = size;
    p_SOL_spriteFont = font;
	Drawable::p_SOL_SB = font->getSpriteBatch();
	m_message = msg;
	Drawable::m_colour = col;
}

UIFloatingText::~UIFloatingText()
{
}
