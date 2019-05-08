#pragma once

#include "UIElement.h"

class UIIcon : public UIElement
{
public:
	UIIcon(glm::vec2 v, int width, int height, Solengine::SpriteBatch* spriteBatch,
		GLuint texture = -1, Solengine::ColourRGBA8 col = { 255, 255, 255, 255 });
	~UIIcon();

	void draw();

	void activate(glm::ivec2 pos);

	void resizeWidth(int w) { m_width = w; }
	void resizeHeight(int h) { m_height = h; }

	void setMultidraw(std::vector<glm::vec2> mdraw) { m_multidraw = mdraw; }

private:
	std::vector<glm::vec2> m_multidraw;
};

