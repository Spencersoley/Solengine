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


		if (m_log.size() > 4 && m_log.size() < 14)
		{
			scrollIcon->resizeHeight(scrollIcon->getHeight()*0.8f);
			scrollIcon->redraw();
		}

		scrollIcon->setPos({ scrollIcon->getPos().x, scrollIconStartYPos });
	} 

	void highlightRecentMessage(bool highlight)
	{
		if (highlight) p_text[0]->setColour({ 255, 155, 40, 255 });
		else p_text[0]->setColour({ 155, 155, 155, 255 });
	}

	void cycleUp()
	{
		if (m_logDisplay + 4 < m_log.size())
		{
			m_logDisplay++;
			changeDisplayedLines(m_logDisplay);
		}
	}

	void cycleDown()
	{
		if (m_logDisplay > 0) 
		{
			m_logDisplay--;
			changeDisplayedLines(m_logDisplay);
		}
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






