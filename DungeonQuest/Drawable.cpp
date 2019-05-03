#include "Drawable.h"

#include <iostream>

Drawable::Drawable()
{
	m_redraw = true;
}

Drawable::~Drawable()
{
}

void Drawable::draw()
{
	if (m_isVisible && m_textureID != -1) 
	{
		if (m_redraw)
		{
			p_SOL_SB->begin();

			const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
			glm::vec4 destRect((float)m_pos.x, (float)m_pos.y, 
				               (float)m_width, (float)m_height);

            p_SOL_SB->draw(destRect, uvRect, m_textureID, 0.0f, m_colour);

			p_SOL_SB->end();
			p_SOL_SB->renderBatch();

			m_redraw = false;
		}
		else p_SOL_SB->renderBatch();
	}
}
