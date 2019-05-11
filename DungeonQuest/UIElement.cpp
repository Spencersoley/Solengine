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

bool UIElement::checkMouseover(glm::vec2 mousePos)
{
	if (mousePos.x > m_pos.x && mousePos.x < m_pos.x + 30 //return true;
		&& mousePos.y > m_pos.y && mousePos.y < m_pos.y + 30) 
		return true;

	return false;
}