#pragma once

#include <Solengine/SpriteBatch.h>

#include <iostream>

class Drawable
{
public:
	Drawable();
	virtual ~Drawable();

	virtual void draw();

	void redraw() { m_redraw = true; }

	//Solengine::SpriteBatch* getSpriteBatch() { return p_SOL_SB; }

	void setTexture(GLuint textureID) { m_textureID = textureID; }
	GLuint getTextureID() const { return m_textureID; }

	void movePos(glm::vec2 pos) { m_pos += pos; redraw(); }
	void setPos(glm::vec2 pos) { m_pos = pos; redraw(); }
	glm::vec2 getPos() { return m_pos; }

	virtual void activate(glm::vec2 pos) {}
	virtual void activate(std::string str, glm::vec2 pos) {}
	virtual bool updateEffect(float adjustedTicks) { return false; }

	float getWidth() { return m_width; }
	float getHeight() { return m_height; }

	void setColour(Solengine::ColourRGBA8 col) { m_colour = col; }
	void setVisible(bool set) { m_isVisible = set; }

	bool m_delete = false;

protected:
	Solengine::SpriteBatch m_SOL_SB;

	bool m_redraw;
	glm::vec2 m_pos;
	float m_height;
    float m_width;
	bool m_isVisible;
	Solengine::ColourRGBA8 m_colour;
	int m_textureID;
};

