#include "UIText.h"

#include <iostream>

UIText::UIText(glm::vec2 v, float size, Solengine::Font* font, std::string msg,
	Solengine::ColourRGBA8 col)
{
	m_pos = (glm::vec2)v;
	m_width = size;
	m_height = size;
	p_SOL_spriteFont = font;
	p_SOL_S = font->getSpriteBatch();
	m_message = msg;
	m_colour = col;

	m_isVisible = true;
}

UIText::~UIText() {}

//we'll continue to use pointers here, because of font, for now
void UIText::draw()
{
	if (!m_isVisible || m_trackedString == "") return;
		
	if (m_redraw) 
	{
		p_SOL_S->begin();

        p_SOL_spriteFont->draw((m_message + m_trackedString).c_str(), 
	        m_pos, { m_width, m_height }, 0.0f, m_colour);

		p_SOL_S->end();
		p_SOL_S->render();

		m_redraw = false;
	}
	else p_SOL_S->render();
}

void UIText::activate(std::string txt, glm::vec2 pos, float duration)
{
	setPos(pos);
	updateText(txt);
	m_duration = duration;
}




