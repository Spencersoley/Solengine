#include "UIText.h"

#include <iostream>

UIText::UIText(int x, int y, int z, Solengine::Font* spriteFont, std::string message)
{
	m_isVisible = true;
	m_pos = { x, y };
	m_width = z;
	m_height = z;
	p_SOL_spriteFont = spriteFont;
	p_SOL_SB = spriteFont->getSpriteBatch();
	m_message = message;
	m_colour = { 255, 255, 255, 255 };
}

UIText::~UIText()
{
}

void UIText::draw()
{
	if (m_trackedString != "" && m_isVisible)
	{
		if (m_redraw)
		{
			p_SOL_SB->begin();

			p_SOL_spriteFont->draw((m_message + m_trackedString).c_str(), m_pos, { m_width, m_height }, 0.0f, m_colour);

			p_SOL_SB->end();
			p_SOL_SB->renderBatch();

			m_redraw = false;
		}
		else
			p_SOL_SB->renderBatch();
	}
}

