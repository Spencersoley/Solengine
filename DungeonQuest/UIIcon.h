#pragma once

#include "UIElement.h"

class UIIcon : public UIElement
{
public:
	UIIcon(int x, int y, int z, int w, GLuint texture, Solengine::SpriteBatch* spriteBatch);
	UIIcon(int x, int y, int z, int w, Solengine::SpriteBatch* spriteBatch);
	~UIIcon();

	void draw();

	void updateIcon(GLuint textureID);
};

