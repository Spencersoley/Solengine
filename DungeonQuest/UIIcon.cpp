#include "UIIcon.h"

#include <iostream>

//This is used when instantiating an icon with a fixed image
UIIcon::UIIcon(int x, int y, int z, int w, Solengine::SpriteBatch* spriteBatch, GLuint texture, Solengine::ColourRGBA8 col)
{
	m_pos = { x, y };
	m_width = z;
	m_height = w;
	p_SOL_SB = spriteBatch;
	m_isVisible = true;
	m_textureID = texture;
	m_colour = col;

}

UIIcon::~UIIcon()
{
}

void UIIcon::redraw()
{
	if (m_isVisible && m_textureID != -1 && m_multidraw.size() == 0)
	{
		p_SOL_SB->begin();

		const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
		glm::vec4 destRect;
		destRect.x = (float)m_pos.x;
		destRect.y = (float)m_pos.y;
		destRect.z = (float)m_width;
		destRect.w = (float)m_height;

		p_SOL_SB->draw(destRect, uvRect, m_textureID, 0.0f, m_colour);

		p_SOL_SB->end();
		p_SOL_SB->renderBatch();
	}
	else if (m_isVisible && m_textureID != -1)
	{
		p_SOL_SB->begin();
		
		for (size_t i = 0; i < m_multidraw.size(); i++)
		{
			const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
			glm::vec4 destRect;
			destRect.x = (float)m_multidraw[i].x;
			destRect.y = (float)m_multidraw[i].y;
			destRect.z = (float)m_width;
			destRect.w = (float)m_height;

			p_SOL_SB->draw(destRect, uvRect, m_textureID, 0.0f, m_colour);
		}

		p_SOL_SB->end();
		p_SOL_SB->renderBatch();
	}
}
