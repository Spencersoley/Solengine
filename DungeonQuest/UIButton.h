#pragma once

#include "UIElement.h"

class UIButton : public UIElement
{
public:
	UIButton(int x, int y, int z, int w, GLuint texture, Solengine::SpriteBatch* spriteBatch);
	UIButton(int x, int y, int z, int w, Solengine::SpriteBatch* spriteBatch);
	~UIButton();

	void draw();

	void updateIcon(GLuint textureID);
};

