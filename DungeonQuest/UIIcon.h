#pragma once

#include "UIElement.h"
#include <Solengine/SpriteBatch.h>

class UIIcon : public UIElement
{
public:
	UIIcon(glm::vec2 v, float width, float height, GLuint texture = -1, 
		Solengine::ColourRGBA8 col = { 255, 255, 255, 255 });
	~UIIcon();

	void draw();

	void activate(glm::vec2 pos, float duration);

	void resizeWidth(float w) { m_width = w; }
	void resizeHeight(float h) { m_height = h; }

	void setMultidraw(std::vector<glm::vec2> mdraw) { m_multidraw = mdraw; }

private:
	std::vector<glm::vec2> m_multidraw;
};

