#include "UIElement.h"

#include <iostream>

UIElement::UIElement() 
{
}

UIElement::~UIElement()
{
}

bool UIElement::updateEffect(float adjustedDeltaTicks)
{
	redraw();
	if (m_duration <= 0) return false;
	
	m_framesPassed++;
	m_duration -= adjustedDeltaTicks;

	if (m_framesPassed % 10 == 0)
	{
		movePos({ 0, 1 });      //We can stabilise the speed of effects. How should we do this?
		if (m_framesPassed > 1000) m_framesPassed = 0;
	}

	return true;
}
