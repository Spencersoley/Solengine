#pragma once

#include "UIElement.h"

class UIButton : public UIElement
{
public:
	UIButton(int x, int y, int z, int w, Solengine::SpriteBatch* spriteBatch, GLuint texture);
	UIButton(int x, int y, int z, int w, Solengine::SpriteBatch* spriteBatch);
	~UIButton();

	void draw(glm::vec2 pos);
	void draw();

	void updateIcon(GLuint textureID);
};

