#include "UIButton.h"

#include <iostream>

UIButton::UIButton(int x, int y, int z, int w, GLuint texture, Solengine::SpriteBatch* spriteBatch)
{
	m_xPos = x;
	m_yPos = y;
	m_width = z;
	m_height = w;

	m_textureID = texture;

	p_SOL_SB = spriteBatch;
}

UIButton::UIButton(int x, int y, int z, int w, Solengine::SpriteBatch* spriteBatch)
{
	m_xPos = x;
	m_yPos = y;
	m_width = z;
	m_height = w;

	m_textureID = -1;

	p_SOL_SB = spriteBatch;
}

UIButton::~UIButton()
{
}

void UIButton::draw()
{
	if (m_textureID != -1)
	{
		//uses Solengine::ResourceManager to grab the textureID, passes it to the spriteBatch.
		//static int textureID = m_textureID;

		static Solengine::ColourRGBA8 colour = { 255, 255, 255, 255 };

		const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

		glm::vec4 destRect;
		destRect.x = (float)m_xPos;
		destRect.y = (float)m_yPos;
		destRect.z = (float)m_width;
		destRect.w = (float)m_height;

		p_SOL_SB->draw(destRect, uvRect, m_textureID, 0.0f, colour);
	}
}

void UIButton::updateIcon(GLuint textureID)
{
	m_textureID = textureID;
}
