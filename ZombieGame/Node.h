#pragma once

#include <glm/glm.hpp>

class Node
{
public:
	Node(int f, int x, int y);
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
	int getDir();

	glm::vec2 getDirectionToChild();
	Node* getParent() { return p_parent;  }
	Node* getChild() { return p_child; }

	void setParent(Node* parent);


	int count;

private:
	void setChild(Node* child);
	void setDirectionToChild();

	int m_xPos;
	int m_yPos;

	glm::vec2 m_dir;

	int m_f; // f = g + h
	int m_g; //cost
	int m_h; //heuristic estimate to goal state
	
	Node* p_parent = nullptr;
	Node* p_child = nullptr;

};

