#include "UIIcon.h"

#include <iostream>

UIIcon::UIIcon(int x, int y, int z, int w, GLuint texture, Solengine::SpriteBatch* spriteBatch)
{
	m_xPos = x;
	m_yPos = y;
	m_width = z;
	m_height = w;

	m_textureID = texture;

	p_SOL_SB = spriteBatch;
}

UIIcon::UIIcon(int x, int y, int z, int w, Solengine::SpriteBatch* spriteBatch)
{
	m_xPos = x;
	m_yPos = y;
	m_width = z;
	m_height = w;

	p_SOL_SB = spriteBatch;
}
UIIcon::~UIIcon()
{
}

void UIIcon::draw(glm::vec2 pos, Solengine::ColourRGBA8 colour)
{
	if (m_textureID != -1)
	{
		const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

		glm::vec4 destRect;
		destRect.x = pos.x;
		destRect.y = pos.y;
		destRect.z = (float)m_width;
		destRect.w = (float)m_height;

		p_SOL_SB->draw(destRect, uvRect, m_textureID, 0.0f, colour);
	}
}

void UIIcon::draw(Solengine::ColourRGBA8 colour)
{
	draw(glm::vec2{ m_xPos, m_yPos }, colour);
}

void UIIcon::draw(glm::vec2 pos)
{
	draw(pos, { 255, 255, 255, 255 } );
}

void UIIcon::draw()
{
	draw(glm::vec2{ m_xPos, m_yPos });
}

void UIIcon::updateIcon(GLuint textureID)
{
	m_textureID = textureID;
}
