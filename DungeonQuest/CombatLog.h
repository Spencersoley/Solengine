#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <map>

#include "UIText.h"


class CombatLog 
{
public:
	CombatLog() {};
	~CombatLog() {};

	std::vector<std::pair<std::string, int>> m_log;

	std::vector<UIText*> p_text;

	void setTexts(std::vector<UIText*> text) { p_text = text; }

	void announce(std::string msg)
	{
		static std::string previousmsg; 
		static int repeatCount;

		if (previousmsg != msg)
		{
			repeatCount = 0;
			m_log.push_back(make_pair(msg, repeatCount));

			if (m_log.size() > 4)
				m_log.erase(m_log.begin());
		} 
		else
		{
			repeatCount++;
			m_log[m_log.size() - 1].second = repeatCount;
		}


		for (size_t i = 0; i < m_log.size(); i++)
		{
			std::cout << m_log[i].first;

			if (m_log[i].second == 0) std::cout << std::endl;
			else std::cout << " (" << m_log[i].second + 1 << ")" << std::endl;
		}
        
		for (size_t i = 0; i < p_text.size(), i < m_log.size(); i++)
		{
			if (m_log[i].second == 0) p_text[i]->updateText(m_log[i].first);
			else p_text[i]->updateText(m_log[i].first + " (" + std::to_string(m_log[i].second + 1) + ")");

			p_text[i]->redraw();
		}

		std::cout << "////////////////////" << std::endl;

		previousmsg = msg;
	}


private: 
};






