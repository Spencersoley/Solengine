#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <map>

#include "UIText.h"

//TODO: FIX SCROLL ICON AND SCALING

class CombatLog 
{
public:
	CombatLog() {};
	~CombatLog() {};

	std::vector<std::string> m_log;
	std::vector<UIText*> p_text;
	UIIcon* scrollIcon = nullptr;

	int m_logDisplay = 0;
	int m_logCapacity = 50;
	int scrollIconStartYPos;
	int scrollIconStartHeight;

	void setScrollIcon(UIIcon* icon) 
	{ 
		scrollIcon = icon; 
		scrollIconStartYPos = icon->getPos().y;
		scrollIconStartHeight = icon->getHeight();
	}

	std::vector<Drawable*> init(int sW, int sH)
	{
		Solengine::ColourRGBA8 col1 = { 255, 155, 40, 255 };
		Solengine::ColourRGBA8 col2 = { 155, 155, 155, 255 };

		const char* font1 = "Fonts/Px437_VGA_SquarePx.ttf";
		int fontSize = 32;
		std::vector<Drawable*> texts;

		UIText* logLineOne = new UIText({ 0.32f*sW, 0.066f*sH }, 0.8f,
			new Solengine::Font(font1, fontSize), " ", col1);
		texts.push_back(logLineOne);
		UIText* logLineTwo = new UIText({ 0.32f*sW, 0.1f*sH }, 0.8f,
			new Solengine::Font(font1, fontSize), " ", col2);
		texts.push_back(logLineTwo);
		UIText* logLineThree = new UIText({ 0.32f*sW, 0.133f*sH }, 0.8f,
			new Solengine::Font(font1, fontSize), " ", col2);
		texts.push_back(logLineThree);
		UIText* logLineFour = new UIText({ 0.32f*sW, 0.166*sH }, 0.8f,
			new Solengine::Font(font1, fontSize), " ", col2);
		texts.push_back(logLineFour);
		
		p_text = { logLineOne, logLineTwo, logLineThree, logLineFour };

		return texts;
	}
	void setTexts(std::vector<UIText*> text) { p_text = text; }

	void announce(std::string msg)
	{
		static std::string previousmsg; 

	
		m_log.insert(m_log.begin(), 1, msg);

		if (m_log.size() > m_logCapacity) m_log.erase(m_log.begin()+m_logCapacity);
		
		for (size_t i = 0; (i < p_text.size() && i < m_log.size()); i++)
		{
	        p_text[i]->updateText(m_log[i]);
			p_text[i]->redraw();
		}

		m_logDisplay = 0;
		changeDisplayedLines(m_logDisplay);

		if (m_log.size() > 4 && m_log.size() < 50)
		{
			scrollIcon->resizeHeight(scrollIconStartHeight * (4.0f / m_log.size()));
			scrollIcon->redraw();
		}

		scrollIcon->setPos({ scrollIcon->getPos().x, scrollIconStartYPos });
	} 

	void highlightRecentMessage(bool highlight)
	{
		if (highlight) p_text[0]->setColour({ 255, 155, 40, 255 });
		else p_text[0]->setColour({ 155, 155, 155, 255 });
	}

	void scrollCombatLog(bool scrollUp)
	{
		if (m_logDisplay + 4 < m_log.size() && scrollUp) m_logDisplay++;
		else if (m_logDisplay > 0 && !scrollUp) m_logDisplay--;
		else return; 
		
		changeDisplayedLines(m_logDisplay);
		scrollIcon->setPos({ scrollIcon->getPos().x, scrollIconStartYPos + (scrollIconStartHeight * ((float)m_logDisplay / m_log.size())) });
		scrollIcon->redraw();
	}

	void changeDisplayedLines(int start)
	{
		for (size_t i = 0; i < p_text.size(); i++)
			if (i < m_log.size() - 1)
			{
				p_text[i]->updateText(m_log[start + i]);
				p_text[i]->redraw();
			}

		if (start == 0) highlightRecentMessage(true);
		else highlightRecentMessage(false);
	}
};






