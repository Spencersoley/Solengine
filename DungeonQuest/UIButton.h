#pragma once

#include "UIElement.h"

class UIButton : public UIElement
{
public:
    UIButton(glm::vec2 v, int width, int height, Solengine::SpriteBatch* spriteBatch,
		     GLuint texture = -1, 
		     Solengine::ColourRGBA8 col = { 255, 255, 255, 255 });
	~UIButton();
};

