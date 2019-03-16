#include "Node.h"

#include <iostream>

Node::Node(int f, int x, int y, int TILE_WIDTH) : m_g(5000), m_h(5000)
{
	m_f = f;
	m_xPos = x * TILE_WIDTH;
	m_yPos = y * TILE_WIDTH;

	m_tileWidth = TILE_WIDTH;

	m_xCoord = x;
	m_yCoord = y;
}

Node::~Node()
{
}

int Node::getDir() 
{
	//point to parent
	if (p_parent != nullptr)
	{
		if (m_xCoord == p_parent->getXCoord() && m_yCoord > p_parent->getYCoord()) return 0;
		if (m_xCoord < p_parent->getXCoord() && m_yCoord > p_parent->getYCoord()) return 1;
		if (m_xCoord < p_parent->getXCoord() && m_yCoord == p_parent->getYCoord()) return 2;
		if (m_xCoord < p_parent->getXCoord() && m_yCoord < p_parent->getYCoord()) return 3;
		if (m_xCoord == p_parent->getXCoord() && m_yCoord < p_parent->getYCoord()) return 4;
		if (m_xCoord > p_parent->getXCoord() && m_yCoord < p_parent->getYCoord()) return 5;
		if (m_xCoord > p_parent->getXCoord() && m_yCoord == p_parent->getYCoord()) return 6;
		if (m_xCoord > p_parent->getXCoord() && m_yCoord > p_parent->getYCoord()) return 7;
	}

	return 9;
}

//Sets the node's parent as the node passed as a parameter. Attempts to set this node as the parent's child
void Node::setParent(Node* parent) 
{ 
	p_parent = parent; 
}

glm::vec2 Node::getDirectionToParent(glm::vec2 startPos)
{ 
	glm::vec2 dir;
	glm::vec2 parentPos; //We need this in world pixels, game coordinates
	
	if (p_parent != nullptr)
	{
		parentPos = { p_parent->getXPos() + 0.5f * m_tileWidth, p_parent->getYPos() + 0.5f * m_tileWidth };
	}
	else
	{
		parentPos = { 0, 0 };
		std::cout << "no parent found" << std::endl;
	}
	
	if (parentPos - startPos == glm::vec2(0, 0))
	{
		dir = { 0, 0 };
		std::cout << "no direction found" << std::endl;
	}
	else
	{
		dir = glm::normalize(parentPos - startPos);
	}

	return dir;
}


