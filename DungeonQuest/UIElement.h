#pragma once

#include <Solengine/SpriteBatch.h>
#include <Solengine/ResourceManager.h>

class UIElement
{
public:
	UIElement();
	virtual ~UIElement();

	virtual void draw() = 0;

	Solengine::SpriteBatch* getSpriteBatch() { return p_SOL_SB; }
	GLuint getTextureID() const { return m_textureID; }

protected:
	int	m_xPos;
	int m_yPos;
	int m_height;
	int m_width;
	Solengine::SpriteBatch* p_SOL_SB;
	Solengine::ColourRGBA8 m_colour;
	GLuint m_textureID;
};

