#include "UIIcon.h"

#include <iostream>

UIIcon::UIIcon(int x, int y, int z, int w, Solengine::SpriteBatch* batch, 
	           GLuint texture, Solengine::ColourRGBA8 col)
{
	m_pos = { x, y };
	m_width = z;
	m_height = w;
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
	        if (m_multidraw.size() == 0)
			{ 
			    p_SOL_SB->begin();

			    const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
                glm::vec4 destRect((float)m_pos.x, (float)m_pos.y, 
					               (float)m_width, (float)m_height);

                p_SOL_SB->draw(destRect, uvRect, m_textureID, 0.0f, m_colour);
		    }
			else
			{
				p_SOL_SB->begin();

				for (size_t i = 0; i < m_multidraw.size(); i++)
				{
					const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
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
