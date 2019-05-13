#pragma once

#include "UIIcon.h"
#include "UIText.h"

class UIButton : public UIElement
{
public:
    UIButton(glm::vec2 v, float width, float height,
        GLuint texture = -1, Solengine::ColourRGBA8 col = { 255, 255, 255, 255 });
	~UIButton();

	bool checkMouseover(glm::vec2 mousePos);

	void setBaseImage(UIIcon* baseImage) { m_baseImage = baseImage; }

	UIIcon* m_baseImage = nullptr;
	UIIcon* m_buttonImage = nullptr;;
	UIText* m_buttonText = nullptr;;
};

