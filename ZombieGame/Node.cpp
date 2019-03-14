#include "Node.h"

Node::Node(int f, int x, int y)
{
	m_f = f;
	m_xPos = x;
	m_yPos = y;
}

Node::~Node()
{
}

glm::vec2 Node::getDir() 
{
	// get its x and y position
	// get its parents x and y position
	// work out direction
	//

	return m_dir;
}
