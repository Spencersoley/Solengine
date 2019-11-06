#include "UIElement.h"

#include <iostream>

UIElement::UIElement() {}

UIElement::~UIElement() {}

bool UIElement::UpdateEffect(float adjustedDeltaTicks)
{
	if (m_duration <= 0) return false;

	Redraw();
	MovePos({ 0, 0.1f });      //We can stabilise the speed of effects. How should we do this?
	m_duration -= adjustedDeltaTicks;

	return true;
}
