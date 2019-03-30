#pragma once

#include "UIElement.h"

class UIButton : public UIElement
{
public:
	UIButton(int x, int y, int z, int w, GLuint textureID, Solengine::SpriteBatch* spriteBatch);
	~UIButton();

	void draw();

	void updateIcon(GLuint textureID);

private:
	GLuint m_textureID;
};

