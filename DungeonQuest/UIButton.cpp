#include "UIButton.h"

#include <iostream>

UIButton::UIButton(int x, int y, int z, int w, GLuint textureID, Solengine::SpriteBatch* spriteBatch)
{
	m_xPos = x;
	m_yPos = y;
	m_width = z;
	m_height = w;
	m_textureID = textureID;

	p_SOL_SB = spriteBatch;
}

UIButton::~UIButton()
{
}

void UIButton::draw()
{
	//uses Solengine::ResourceManager to grab the textureID, passes it to the spriteBatch.
	//static int textureID = m_textureID;

	static Solengine::ColourRGBA8 colour = { 255, 255, 255, 255 };

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = m_xPos;
	destRect.y = m_yPos;
	destRect.z = m_width;
	destRect.w = m_height;

	p_SOL_SB->draw(destRect, uvRect, m_textureID, 0.0f, colour);
}
