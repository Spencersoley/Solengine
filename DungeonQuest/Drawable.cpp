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
	if (!m_isVisible || m_textureID == -1) return;

	if (m_redraw)
	{
		const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
		glm::vec4 destRect(m_pos.x, m_pos.y,
			m_width, m_height);

		p_SOL_S->draw(destRect, uvRect, m_textureID, 0.0f, m_colour);

		p_SOL_S->end();
		p_SOL_S->render();

		m_redraw = false;
	}
	else p_SOL_S->render();
}

