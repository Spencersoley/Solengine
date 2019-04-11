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



