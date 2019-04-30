#pragma once

#include "UIText.h"

class FloatingDamageText : public UIText
{
public:
	FloatingDamageText() {};
	FloatingDamageText(glm::vec2 v, int size, Solengine::Font* font, std::string msg,
		Solengine::ColourRGBA8 col = { 255, 255, 255, 255 });
	~FloatingDamageText();

	float m_lifeTime;

	void activate(glm::ivec2 tarPos, std::string msg);
	void deactivate();

	void update(float adjustedDeltaTicks);
};

