#include "UIIcon.h"

#include <iostream>

UIIcon::UIIcon(glm::vec2 v, float width, float height,
	GLuint texture, Solengine::ColourRGBA8 col)
{
	m_pos = (glm::ivec2)v;
	m_width = width;
	m_height = height;
	m_isVisible = true;
	m_textureID = texture;
	m_colour = col;
}

UIIcon::~UIIcon()
{
}

void UIIcon::draw()
{
	if (m_isVisible && m_textureID != -1)
	    if (m_redraw)
		{ 
			m_SOL_SB.begin();
			const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	        if (m_multidraw.empty())
			{ 
                glm::vec4 destRect(m_pos.x, m_pos.y, 
					               m_width, m_height);

				m_SOL_SB.draw(destRect, uvRect, m_textureID, 0.0f, m_colour);
		    }
			else
			{
				for (size_t i = 0; i < m_multidraw.size(); i++)
				{
                    glm::vec4 destRect(m_multidraw[i].x, 
						               m_multidraw[i].y, m_width, 
						               m_height);
	
					m_SOL_SB.draw(destRect, uvRect, m_textureID, 0.0f,
						           m_colour);
				}
			}
			
			m_SOL_SB.end();
			m_SOL_SB.renderBatch();
			m_redraw = false;
		}
		else m_SOL_SB.renderBatch();
}

void UIIcon::activate(glm::vec2 pos)
{
	setPos(pos);
	setVisible(true);
	m_duration = 10;
}
