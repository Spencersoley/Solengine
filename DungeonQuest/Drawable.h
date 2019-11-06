#pragma once

#include <Solengine/SpriteBatch.h>
#include <Solengine/SpriteSingle.h>

#include <iostream>

class Drawable
{
public:
	Drawable();
	~Drawable();

	// SETTERS //
	void SetColour(Solengine::ColourRGBA8 col) { m_colour = col; }
	void SetVisible(bool set) { m_isVisible = set; }
	void SetTexture(GLuint textureID) { m_textureID = textureID; }
	void SetPos(glm::vec2 pos) { m_pos = pos; Redraw(); }
	
	// GETTERS //
	glm::vec2 GetPos() const { return m_pos; }
	GLuint GetTextureID() const { return m_textureID; }
	float GetWidth() const { return m_width; }
	float GetHeight() const { return m_height; }

	virtual void Draw();

	void Redraw() { m_redraw = true; }


	void MovePos(glm::vec2 pos) { m_pos += pos; Redraw(); }
	virtual void Activate(glm::vec2 pos, float duration) {}
	virtual void Activate(std::string str, glm::vec2 pos, float duration) {}
	virtual bool UpdateEffect(float adjustedTicks) { return false; }

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

