#include "UIButton.h"

#include <iostream>

UIButton::UIButton(glm::vec2 v, int width, int height, Solengine::SpriteBatch* batch,
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

UIButton::~UIButton()
{
}

