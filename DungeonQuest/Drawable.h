#pragma once

#include <Solengine/SpriteBatch.h>
#include <Solengine/SpriteSingle.h>

#include <iostream>

class Drawable
{
public:
	Drawable();
	virtual ~Drawable();

	// SETTERS //
	void setColour(Solengine::ColourRGBA8 col) { m_colour = col; }
	void setVisible(bool set) { m_isVisible = set; }
	void setTexture(GLuint textureID) { m_textureID = textureID; }
	void setPos(glm::vec2 pos) { m_pos = pos; redraw(); }
	
	// GETTERS //
	glm::vec2 getPos() const { return m_pos; }
	GLuint getTextureID() const { return m_textureID; }
	float getWidth() const { return m_width; }
	float getHeight() const { return m_height; }

	virtual void draw();

	void redraw() { m_redraw = true; }


	void movePos(glm::vec2 pos) { m_pos += pos; redraw(); }
	virtual void activate(glm::vec2 pos) {}
	virtual void activate(std::string str, glm::vec2 pos) {}
	virtual bool updateEffect(float adjustedTicks) { return false; }

	bool m_delete = false;

protected:
	Solengine::SpriteBase* p_SOL_S = nullptr;

	bool m_redraw;
	glm::vec2 m_pos;
	float m_height;
    float m_width;
	bool m_isVisible;
	Solengine::ColourRGBA8 m_colour;
	int m_textureID;
};

