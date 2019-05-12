#include "UIButton.h"

#include <iostream>

UIButton::UIButton(glm::vec2 v, float width, float height, Solengine::SpriteBatch* batch,
	               GLuint texture, Solengine::ColourRGBA8 col)
{
	m_pos = (glm::ivec2)v;
	m_width = width;
	m_height = height;
	m_isVisible = true;
	m_textureID = texture;
	m_colour = col;
}

UIButton::~UIButton()
{
}

bool UIButton::checkMouseover(glm::vec2 mousePos)
{
	if (mousePos.x > m_pos.x && mousePos.x < m_pos.x + 30 //return true;
		&& mousePos.y > m_pos.y && mousePos.y < m_pos.y + 30)
		return true;

	return false;
}