#pragma once

#include <glm/glm.hpp>

class Node
{
public:
	Node(int f, int x, int y, int TILE_WIDTH);
	~Node();

	void setf(int value) { m_f = value; }
	void updatef() { m_f = m_g + m_h; }
	void setg(int value) { m_g = value; }
	void seth(int value) { m_h = value; }
	int getf() { return m_f; }
	int getg() { return m_g; }
	int geth() { return m_h; }

	int getXPos() { return m_xPos; } 
	int getYPos() { return m_yPos; } 

	int getXCoord() { return m_xCoord; }
	int getYCoord() { return m_yCoord; }

	int getDir();

	glm::vec2 getDirectionToParent(glm::vec2 startPos);
	Node* getParent() { return p_parent;  }

	void setParent(Node* parent);


	int count;

private:
	int m_xPos;
	int m_yPos;
	int m_xCoord;
	int m_yCoord;

	int m_tileWidth;
	glm::vec2 m_dir;

	int m_f; // f = g + h
	int m_g; //cost
	int m_h; //heuristic estimate to goal state
	
	Node* p_parent = nullptr;
};

