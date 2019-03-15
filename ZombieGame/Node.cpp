#include "Node.h"

Node::Node(int f, int x, int y) : m_g(5000), m_h(0)
{
	m_f = f;
	m_xPos = x;
	m_yPos = y;
}

Node::~Node()
{
}

int Node::getDir() 
{
	//point to parent

	if (m_xPos == p_parent->getXPos() && m_yPos > p_parent->getYPos()) return 0;
	if (m_xPos < p_parent->getXPos() && m_yPos > p_parent->getYPos()) return 1;
	if (m_xPos < p_parent->getXPos() && m_yPos == p_parent->getYPos()) return 2;
	if (m_xPos < p_parent->getXPos() && m_yPos < p_parent->getYPos()) return 3;
	if (m_xPos == p_parent->getXPos() && m_yPos < p_parent->getYPos()) return 4;
	if (m_xPos > p_parent->getXPos() && m_yPos < p_parent->getYPos()) return 5;
	if (m_xPos > p_parent->getXPos() && m_yPos == p_parent->getYPos()) return 6;
	if (m_xPos > p_parent->getXPos() && m_yPos > p_parent->getYPos()) return 7;

	else return 9;
}
