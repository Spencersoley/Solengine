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
		m_SOL_SB.begin();

		const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
		glm::vec4 destRect(m_pos.x, m_pos.y, 
		    m_width, m_height);

        m_SOL_SB.draw(destRect, uvRect, m_textureID, 0.0f, m_colour);

	    m_SOL_SB.end();
	    m_SOL_SB.renderBatch();

		m_redraw = false;
	}
	else m_SOL_SB.renderBatch();
}
