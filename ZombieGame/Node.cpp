#include "Node.h"

#include <iostream>

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
	//point to child
	if (p_child != nullptr)
	{
		if (m_xPos == p_child->getXPos() && m_yPos > p_child->getYPos()) return 0;
		if (m_xPos < p_child->getXPos() && m_yPos > p_child->getYPos()) return 1;
		if (m_xPos < p_child->getXPos() && m_yPos == p_child->getYPos()) return 2;
		if (m_xPos < p_child->getXPos() && m_yPos < p_child->getYPos()) return 3;
		if (m_xPos == p_child->getXPos() && m_yPos < p_child->getYPos()) return 4;
		if (m_xPos > p_child->getXPos() && m_yPos < p_child->getYPos()) return 5;
		if (m_xPos > p_child->getXPos() && m_yPos == p_child->getYPos()) return 6;
		if (m_xPos > p_child->getXPos() && m_yPos > p_child->getYPos()) return 7;
	}

	return 9;
}

//Sets the node's parent as the node passed as a parameter. Attempts to set this node as the parent's child
void Node::setParent(Node* parent) 
{ 
	p_parent = parent; 
	parent->setChild(this);
}

//if main child node doesn't exist, new child is set as the main child
//if it does exist, the if the new child has a lower f value than main child, new child is set as the main child
void Node::setChild(Node* child)
{
	if (p_child != nullptr) 
	{	
		if (child->getf() < p_child->getf())
		{
			p_child = child;
		}
	}
	else
	{
		p_child = child;
	}
}

void Node::setDirectionToChild()
{
	glm::vec2 childPos;
	glm::vec2 nodePos{ m_xPos, m_yPos };

	if (p_child == nullptr)
	{
		childPos = { 0, 0 };
	}
	else
	{
		childPos = { p_child->getXPos(), p_child->getYPos() };
	}

	if (childPos - nodePos == glm::vec2(0, 0))
	{
		m_dir = { 0, 0 };
	}
	else
	{
		m_dir = glm::normalize(childPos - nodePos);
	}
}

glm::vec2 Node::getDirectionToChild() 
{ 
	setDirectionToChild();
	std::cout << m_dir.x << " " << m_dir.y << std::endl;
	return m_dir;
}

