#include "UIIcon.h"


#include <iostream>

UIIcon::UIIcon(glm::vec2 v, float width, float height,
	GLuint texture, Solengine::ColourRGBA8 col)
{
	m_pos = (glm::ivec2)v;
	m_width = width;
	m_height = height;
	m_textureID = texture;
	m_colour = col;
 
	p_SOL_S = new Solengine::SpriteBatch();
	m_isVisible = true;
}

UIIcon::~UIIcon() { delete p_SOL_S;  }

void UIIcon::Draw()
{
	if (!m_isVisible || m_textureID == -1) return;
	    
    if (m_redraw)
	{ 
		p_SOL_S->Begin();
		const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	    if (m_multidraw.empty())
		{ 
            glm::vec4 destRect(m_pos.x, m_pos.y, 
				m_width, m_height);

			p_SOL_S->Draw(destRect, uvRect, m_textureID, 0.0f, m_colour);
		}
		else
		{
			for (size_t i = 0; i < m_multidraw.size(); i++)
			{
                glm::vec4 destRect(m_multidraw[i].x, 
				    m_multidraw[i].y, m_width, m_height);
	
				p_SOL_S->Draw(destRect, uvRect, m_textureID, 0.0f, m_colour);
			}
		}
			
		p_SOL_S->End();
		p_SOL_S->Render();
		m_redraw = false;
	}
	else p_SOL_S->Render();
}

void UIIcon::Activate(glm::vec2 pos, float duration)
{
	SetPos(pos);
	m_duration = duration;
}
