#pragma once

#include <Solengine/SpriteBatch.h>

class Drawable
{
public:
	Drawable();
	virtual ~Drawable();

	virtual void redraw();
	virtual void draw();

	Solengine::SpriteBatch* getSpriteBatch() { return p_SOL_SB; }

	void setTexture(GLuint textureID) { m_textureID = textureID; }
	GLuint getTextureID() const { return m_textureID; }

	void setPos(glm::ivec2 pos) { m_pos = pos; }
	glm::ivec2 getPos() { return m_pos; }

	void setColour(Solengine::ColourRGBA8 col) { m_colour = col; }

	void setVisible(bool set) { m_isVisible = set; }

protected:
	Solengine::SpriteBatch* p_SOL_SB;

	glm::ivec2 m_pos;
	int m_height;
	int m_width;
	bool m_isVisible;
	Solengine::ColourRGBA8 m_colour;
	int m_textureID;
};

