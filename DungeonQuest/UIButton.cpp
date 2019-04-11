#include "UIButton.h"

#include <iostream>

UIButton::UIButton(int x, int y, int z, int w, Solengine::SpriteBatch* spriteBatch, GLuint texture, Solengine::ColourRGBA8 col)
{
	m_pos = { x, y };
	m_width = z;
	m_height = w;
	p_SOL_SB = spriteBatch;
	m_isVisible = true;
	m_textureID = texture;
	m_colour = col;
}

UIButton::~UIButton()
{
}

