#include "UIText.h"

#include <iostream>

UIText::UIText(glm::vec2 v, int size, Solengine::Font* font, std::string msg,
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

UIText::~UIText()
{
}

void UIText::draw()
{
	if (m_trackedString != "" && m_isVisible)
		if (m_redraw) 
		{
			p_SOL_SB->begin();

            p_SOL_spriteFont->draw((m_message + m_trackedString).c_str(), 
				                   m_pos, { m_width, m_height }, 0.0f, 
				                   m_colour);

			p_SOL_SB->end();
			p_SOL_SB->renderBatch();

			m_redraw = false;
		}
		else p_SOL_SB->renderBatch();
}

