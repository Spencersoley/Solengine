#include "UIIcon.h"

#include <iostream>

UIIcon::UIIcon(glm::vec2 v, int width, int height, Solengine::SpriteBatch* batch,
	GLuint texture, Solengine::ColourRGBA8 col)
{
	m_pos = (glm::ivec2)v;
	m_width = width;
	m_height = height;
	p_SOL_SB = batch;
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
			p_SOL_SB->begin();
			const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	        if (m_multidraw.empty())
			{ 
                glm::vec4 destRect((float)m_pos.x, (float)m_pos.y, 
					               (float)m_width, (float)m_height);

                p_SOL_SB->draw(destRect, uvRect, m_textureID, 0.0f, m_colour);
		    }
			else
			{
				for (size_t i = 0; i < m_multidraw.size(); i++)
				{
                    glm::vec4 destRect((float)m_multidraw[i].x, 
						               m_multidraw[i].y, (float)m_width, 
						               (float)m_height);
	
					p_SOL_SB->draw(destRect, uvRect, m_textureID, 0.0f, 
						           m_colour);
				}
			}
			
			p_SOL_SB->end();
			p_SOL_SB->renderBatch();		
			m_redraw = false;
		}
		else p_SOL_SB->renderBatch();
}

void UIIcon::activate(glm::ivec2 pos)
{
	setPos(pos);
	setVisible(true);
	m_duration = 10;
}
