#pragma once

#include "UIElement.h"

class UIIcon : public UIElement
{
public:
	UIIcon(int x, int y, int z, int w, Solengine::SpriteBatch* spriteBatch, GLuint texture = -1, Solengine::ColourRGBA8 col = { 255, 255, 255, 255 });

	~UIIcon();

	void draw(glm::vec2 pos, Solengine::ColourRGBA8 colour);
	void draw(Solengine::ColourRGBA8 colour);
	void draw(glm::vec2 pos);
	void draw();

	void updateIcon(GLuint textureID);
};

