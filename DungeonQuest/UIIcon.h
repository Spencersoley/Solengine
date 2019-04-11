#pragma once

#include "UIElement.h"

class UIIcon : public UIElement
{
public:
	UIIcon(int x, int y, int z, int w, Solengine::SpriteBatch* spriteBatch, GLuint texture = -1, Solengine::ColourRGBA8 col = { 255, 255, 255, 255 });
	~UIIcon();
};

