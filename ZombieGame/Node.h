#pragma once

#include <glm/glm.hpp>
#include <iostream>

struct Node
{
	Node(int f, int x, int y, int TILE_WIDTH)
	{
		m_f = f;
		m_xPos = x * TILE_WIDTH;
		m_yPos = y * TILE_WIDTH;

		m_tileWidth = TILE_WIDTH;

		m_xCoord = x;
		m_yCoord = y;
	}
	~Node()
	{
	}
	
	void updatef() { m_f = m_g + m_h; }

	int m_xPos;
	int m_yPos;
	int m_xCoord;
	int m_yCoord;
	int m_f; // f = g + h
	int m_g; //cost
	int m_h; //heuristic estimate to goal state
	Node* p_parent = nullptr;
	int m_tileWidth;

};

