#include "Pathfinder.h"

#include <iostream>
#include <math.h>  

//Better way than redefining here, this is temporary
const float AGENT_WIDTH = 40.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

Pathfinder::Pathfinder()
{
}

Pathfinder::~Pathfinder()
{
}

void Pathfinder::init(std::vector<std::vector<Node>> nodeField, int tileWidth)
{
	m_field = nodeField;
	m_tileWidth = tileWidth;
}

glm::vec2 Pathfinder::pathfind(glm::vec2 pos, glm::vec2 target)
{
	glm::vec2 dir = { 0, 0 };
	glm::vec2 targetCoords = getCoordinates(target);
	glm::vec2 coords = getCoordinates(pos);

	//std::cout << m_field[coords.y][coords.x].getValue() << std::endl;

	//set direction based on which neighbour has the lowest f score

	if (m_previousTargetCoords != targetCoords)
	{
		//recalculate path;


		m_field[coords.y][coords.x].setf(0);

		updateNeighbourNodes(coords);

		//do while target coords and checked coords differ OR open set is empty
		//check through open set, holding the coords associated with the lowest f score
		//updateneighbournodes of lowest f node updateNeighbourNodes(coords);
		

		//set dir in all m_field's nodes. Dir will lead pathfinder to target

		for (int y = 0; y < m_field.size(); y++)
		{
			for (int x = 0; x < m_field[0].size(); x++)
			{
				std::cout << m_field[y][x].getf();
			}

			std::cout << std::endl;
		}
	}

    dir = m_field[coords.y][coords.x].getDir();

	m_previousTargetCoords = targetCoords;
	return dir;
}

glm::vec2 Pathfinder::getCoordinates(glm::vec2 position)
{
	glm::vec2 coordinates;

	coordinates.x = floor((position.x + AGENT_RADIUS) / m_tileWidth);
	coordinates.y = floor((position.y + AGENT_RADIUS) / m_tileWidth);

	return coordinates;
}

void Pathfinder::updateNeighbourNodes(glm::vec2 nodeCoords)
{
	float nodeValue = m_field[nodeCoords.y][nodeCoords.x].getf();

	//upper node (lower on output)
	// if coords not in closed set
	if (nodeCoords.y + 1 < m_field.size())
	{
		if (m_field[nodeCoords.y + 1][nodeCoords.x].getf() > 0)
		{
			m_field[nodeCoords.y + 1][nodeCoords.x].setg(nodeValue + 1);
			// set h as |targetxcoords - xcoords| + |targetycoords - ycoords|
			m_field[nodeCoords.y + 1][nodeCoords.x].updatef();
			//if coords not in open set
			  //add to open set
		}
	}
	//lower node (upper on output)
	// if coords not in closed set
	if (nodeCoords.y - 1 >= 0)
	{
		if (m_field[nodeCoords.y - 1][nodeCoords.x].getf() > 0)
		{
			m_field[nodeCoords.y - 1][nodeCoords.x].setg(nodeValue + 1);
			// set h as |targetxcoords - xcoords| + |targetycoords - ycoords|
			m_field[nodeCoords.y - 1][nodeCoords.x].updatef();
			//if coords not in open set
			  //add to open set
		}
	}
	//right node
	// if coords not in closed set
	if (nodeCoords.x + 1 < m_field[0].size())
	{
		if (m_field[nodeCoords.y][nodeCoords.x + 1].getf() > 0)
		{
			m_field[nodeCoords.y][nodeCoords.x + 1].setg(nodeValue + 1);
			// set h as |targetxcoords - xcoords| + |targetycoords - ycoords|
			m_field[nodeCoords.y][nodeCoords.x + 1].updatef();
			//if coords not in open set
			  //add to open set
		}
	}
	//left node
	// if coords not in closed set
	if (nodeCoords.x - 1 >= 0)
	{
		if (m_field[nodeCoords.y][nodeCoords.x - 1].getf() > 0)
		{
			m_field[nodeCoords.y][nodeCoords.x - 1].setg(nodeValue + 1);
			// set h as |targetxcoords - xcoords| + |targetycoords - ycoords|
			m_field[nodeCoords.y][nodeCoords.x - 1].updatef();
			//if coords not in open set
			  //add to open set
		}
	}
	//upper right node (lower right on output)
    // if coords not in closed set
	if (nodeCoords.y + 1 < m_field.size() && nodeCoords.x + 1 < m_field[0].size())
	{
		if (m_field[nodeCoords.y + 1][nodeCoords.x + 1].getf() > 0)
		{
			m_field[nodeCoords.y + 1][nodeCoords.x + 1].setg(2);
			// set h as |targetxcoords - xcoords| + |targetycoords - ycoords|
			m_field[nodeCoords.y + 1][nodeCoords.x + 1].updatef();
			//if coords not in open set
			  //add to open set
		}
	}
	//upper left node (lower left on output)
	// if coords not in closed set
	if (nodeCoords.y + 1 < m_field.size() && nodeCoords.x - 1 > 0)
	{
		if (m_field[nodeCoords.y + 1][nodeCoords.x - 1].getf() > 0)
		{
			m_field[nodeCoords.y + 1][nodeCoords.x - 1].setg(2);
			// set h as |targetxcoords - xcoords| + |targetycoords - ycoords|
			m_field[nodeCoords.y + 1][nodeCoords.x - 1].updatef();
			//if coords not in open set
			  //add to open set
		}
	}
	//lower right node (upper right on output)
	// if coords not in closed set
	if (nodeCoords.y - 1 > 0 && nodeCoords.x + 1 < m_field[0].size())
	{
		if (m_field[nodeCoords.y - 1][nodeCoords.x + 1].getf() > 0)
		{
			m_field[nodeCoords.y - 1][nodeCoords.x + 1].setg(2);
			// set h as |targetxcoords - xcoords| + |targetycoords - ycoords|
			m_field[nodeCoords.y - 1][nodeCoords.x + 1].updatef();
			//if coords not in open set
			  //add to open set
		}
	}
	//lower left node (upper left on output)
	// if coords not in closed set
	if (nodeCoords.y - 1 > 0 && nodeCoords.x - 1 > 0)
	{
		if (m_field[nodeCoords.y - 1][nodeCoords.x - 1].getf() > 0)
		{
			m_field[nodeCoords.y - 1][nodeCoords.x - 1].setg(2);
			// set h as |targetxcoords - xcoords| + |targetycoords - ycoords|
			m_field[nodeCoords.y - 1][nodeCoords.x - 1].updatef();
			//if coords not in open set
			  //add to open set
		}
	}

	// remove from open set
	// add to closed set
}
