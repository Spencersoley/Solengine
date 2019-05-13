#include "UIElement.h"

#include <iostream>

UIElement::UIElement() {}

UIElement::~UIElement() {}

bool UIElement::updateEffect(float adjustedDeltaTicks)
{
	if (m_duration <= 0) return false;

	redraw();
	m_duration -= adjustedDeltaTicks;
	movePos({ 0, 0.1f });      //We can stabilise the speed of effects. How should we do this?

	return true;
}
