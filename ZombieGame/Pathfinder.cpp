#include "Pathfinder.h"

#include <iostream>
#include <math.h> 
#include <cmath>
#include <algorithm>

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

	if (m_previousTargetCoords != targetCoords)
	{	
		m_openSet.clear();
		m_closedSet.clear();
		
		m_field[coords.y][coords.x].seth(10 * (abs(targetCoords.x - coords.x) + abs(targetCoords.y - coords.y)));
		m_field[coords.y][coords.x].updatef();
		m_openSet.push_back(coords);
		glm::vec2 pathCoords = coords;
		
		while (pathCoords != targetCoords) //and also while open set is not empty
		{
		    updateNeighbourNodes(pathCoords, targetCoords);
		    pathCoords = getLowestf(m_openSet);
		}

		//set dir in all m_field's nodes. Dir will lead pathfinder to target
			
		//announce map
		for (int y = 0; y < m_field.size(); y++)
		{
			for (int x = 0; x < m_field[0].size(); x++)
			{
				if (m_field[y][x].getf() < 0)
				{
					std::cout << "x";
				}
				else if (m_field[y][x].getXPos() == targetCoords.x && m_field[y][x].getYPos() == targetCoords.y)
				{
					std::cout << "T";
				}
				else if (m_field[y][x].getf() == 5000)
				{
					std::cout << "_";
					
				}
				else if (std::find(m_closedSet.begin(), m_closedSet.end(), glm::vec2{ m_field[y][x].getXPos(), m_field[y][x].getYPos() }) != m_closedSet.end())
				{
					if (m_field[y][x].getf() > 9)
					{
						std::cout << "*";
					}
					else
					{
						std::cout <<  m_field[y][x].getf();
					}
				}
				else
				{
					std::cout << " ";
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

		//reset nodes
		for (int y = 0; y < m_field.size(); y++)
		{
			for (int x = 0; x < m_field[0].size(); x++)
			{
				if (m_field[y][x].getf() >= 0)
				{
					m_field[y][x].setf(5000);
					m_field[y][x].setg(0);
					m_field[y][x].seth(0);
				}
			}
		}
	}   

	m_previousTargetCoords = targetCoords;

	dir = m_field[coords.y][coords.x].getDir();
	return dir;
}

glm::vec2 Pathfinder::getCoordinates(glm::vec2 position)
{
	glm::vec2 coordinates;

	coordinates.x = floor((position.x + AGENT_RADIUS) / m_tileWidth);
	coordinates.y = floor((position.y + AGENT_RADIUS) / m_tileWidth);

	return coordinates;
}

//We can avoid a lot of repetition here.
void Pathfinder::updateNeighbourNodes(glm::vec2 nodeCoords, glm::vec2 targetCoords)
{
	float nodeg = m_field[nodeCoords.y][nodeCoords.x].getg();

	//upper node (lower on output)
	if(std::find(m_closedSet.begin(), m_closedSet.end(), glm::vec2 { nodeCoords.x, nodeCoords.y + 1 }) == m_closedSet.end()) 
	{
		if (nodeCoords.y + 1 < m_field.size())
		{
			if (m_field[nodeCoords.y + 1][nodeCoords.x].getf() > 0)
			{
				//only do this if the likely f value is lower than the current f value
				if (m_field[nodeCoords.y + 1][nodeCoords.x].getf() > 10 * (abs(targetCoords.x - nodeCoords.x) + abs(targetCoords.y - (nodeCoords.y + 1))) + nodeg + 10)
				{
					m_field[nodeCoords.y + 1][nodeCoords.x].setg(nodeg + 10);
					m_field[nodeCoords.y + 1][nodeCoords.x].seth(10 * (abs(targetCoords.x - nodeCoords.x) + abs(targetCoords.y - (nodeCoords.y + 1))));
					m_field[nodeCoords.y + 1][nodeCoords.x].updatef();
					//if not already in the open set, add it to the open set and set its parent as the current searching node
					//if already in the open set, change its parent to the current searching node as it provides a better f value
					if (std::find(m_openSet.begin(), m_openSet.end(), glm::vec2{ nodeCoords.x, nodeCoords.y + 1 }) == m_openSet.end())
					{
						m_openSet.push_back(glm::vec2{ nodeCoords.x, nodeCoords.y + 1 });
						//set parent as searching node
					}
					else
					{
						//set parent as searching node
					}
				}
			}
		}
	}
	//lower node (upper on output)
	if (std::find(m_closedSet.begin(), m_closedSet.end(), glm::vec2{ nodeCoords.x, nodeCoords.y - 1 }) == m_closedSet.end())
	{
		if (nodeCoords.y - 1 >= 0)
		{
			if (m_field[nodeCoords.y - 1][nodeCoords.x].getf() > 0)
			{
				if (m_field[nodeCoords.y - 1][nodeCoords.x].getf() > 10 * (abs(targetCoords.x - nodeCoords.x) + abs(targetCoords.y - (nodeCoords.y - 1))) + nodeg + 10)
				{
					m_field[nodeCoords.y - 1][nodeCoords.x].setg(nodeg + 10);
					m_field[nodeCoords.y - 1][nodeCoords.x].seth(10 * (abs(targetCoords.x - nodeCoords.x) + abs(targetCoords.y - (nodeCoords.y - 1))));
					m_field[nodeCoords.y - 1][nodeCoords.x].updatef();
					if (std::find(m_openSet.begin(), m_openSet.end(), glm::vec2{ nodeCoords.x, nodeCoords.y - 1 }) == m_openSet.end())
					{
						m_openSet.push_back(glm::vec2{ nodeCoords.x, nodeCoords.y - 1 });
					}
				}
			}
		}
	}
	//right node
	if (std::find(m_closedSet.begin(), m_closedSet.end(), glm::vec2{ nodeCoords.x + 1, nodeCoords.y }) == m_closedSet.end())
	{
		if (nodeCoords.x + 1 < m_field[0].size())
		{
			if (m_field[nodeCoords.y][nodeCoords.x + 1].getf() > 0)
			{
				if (m_field[nodeCoords.y][nodeCoords.x + 1].getf() > 10 * (abs(targetCoords.x - (nodeCoords.x + 1)) + abs(targetCoords.y - nodeCoords.y)) + nodeg + 10)
				{
					m_field[nodeCoords.y][nodeCoords.x + 1].setg(nodeg + 10);
					m_field[nodeCoords.y][nodeCoords.x + 1].seth(10 * (abs(targetCoords.x - (nodeCoords.x + 1)) + abs(targetCoords.y - nodeCoords.y)));
					m_field[nodeCoords.y][nodeCoords.x + 1].updatef();
					if (std::find(m_openSet.begin(), m_openSet.end(), glm::vec2{ nodeCoords.x + 1, nodeCoords.y }) == m_openSet.end())
					{
						m_openSet.push_back(glm::vec2{ nodeCoords.x + 1, nodeCoords.y });
					}
				}
			}
		}
	}
	//left node
	if (std::find(m_closedSet.begin(), m_closedSet.end(), glm::vec2{ nodeCoords.x - 1, nodeCoords.y }) == m_closedSet.end())
	{
		if (nodeCoords.x - 1 >= 0)
		{
			if (m_field[nodeCoords.y][nodeCoords.x - 1].getf() > 0)
			{
				if (m_field[nodeCoords.y][nodeCoords.x - 1].getf() > 10 * (abs(targetCoords.x - (nodeCoords.x - 1)) + abs(targetCoords.y - nodeCoords.y)) + nodeg + 10)
				{
					m_field[nodeCoords.y][nodeCoords.x - 1].setg(nodeg + 10);
					m_field[nodeCoords.y][nodeCoords.x - 1].seth(10 * (abs(targetCoords.x - (nodeCoords.x - 1)) + abs(targetCoords.y - nodeCoords.y)));
					m_field[nodeCoords.y][nodeCoords.x - 1].updatef();
					if (std::find(m_openSet.begin(), m_openSet.end(), glm::vec2{ nodeCoords.x - 1, nodeCoords.y }) == m_openSet.end())
					{
						m_openSet.push_back(glm::vec2{ nodeCoords.x - 1, nodeCoords.y });
					}
				}
			}
		}
	}
	//upper right node (lower right on output)
	if (std::find(m_closedSet.begin(), m_closedSet.end(), glm::vec2{ nodeCoords.x + 1, nodeCoords.y + 1 }) == m_closedSet.end())
	{
		if (nodeCoords.y + 1 < m_field.size() && nodeCoords.x + 1 < m_field[0].size())
		{
			if (m_field[nodeCoords.y + 1][nodeCoords.x + 1].getf() > 0)
			{
				if (m_field[nodeCoords.y + 1][nodeCoords.x + 1].getf() > 10 * (abs(targetCoords.x - (nodeCoords.x + 1)) + abs(targetCoords.y - (nodeCoords.y + 1))) + nodeg + 14)
				{
					m_field[nodeCoords.y + 1][nodeCoords.x + 1].setg(nodeg + 14);
					m_field[nodeCoords.y + 1][nodeCoords.x + 1].seth(10 * (abs(targetCoords.x - (nodeCoords.x + 1)) + abs(targetCoords.y - (nodeCoords.y + 1))));
					m_field[nodeCoords.y + 1][nodeCoords.x + 1].updatef();
					if (std::find(m_openSet.begin(), m_openSet.end(), glm::vec2{ nodeCoords.x + 1, nodeCoords.y + 1 }) == m_openSet.end())
					{
						m_openSet.push_back(glm::vec2{ nodeCoords.x + 1, nodeCoords.y + 1 });
					}
				}
			}
		}
	}
	//upper left node (lower left on output)
	if (std::find(m_closedSet.begin(), m_closedSet.end(), glm::vec2{ nodeCoords.x - 1, nodeCoords.y + 1 }) == m_closedSet.end())
	{
		if (nodeCoords.y + 1 < m_field.size() && nodeCoords.x - 1 > 0)
		{
			if (m_field[nodeCoords.y + 1][nodeCoords.x - 1].getf() > 0)
			{
				if (m_field[nodeCoords.y + 1][nodeCoords.x - 1].getf() > 10 * (abs(targetCoords.x - (nodeCoords.x - 1)) + abs(targetCoords.y - (nodeCoords.y + 1))) + nodeg + 14)
				{
					m_field[nodeCoords.y + 1][nodeCoords.x - 1].setg(nodeg + 14);
					m_field[nodeCoords.y + 1][nodeCoords.x - 1].seth(10 * (abs(targetCoords.x - (nodeCoords.x - 1)) + abs(targetCoords.y - (nodeCoords.y + 1))));
					m_field[nodeCoords.y + 1][nodeCoords.x - 1].updatef();
					if (std::find(m_openSet.begin(), m_openSet.end(), glm::vec2{ nodeCoords.x - 1, nodeCoords.y + 1 }) == m_openSet.end())
					{
						m_openSet.push_back(glm::vec2{ nodeCoords.x - 1, nodeCoords.y + 1 });
					}
				}
			}
		}
	}
	//lower right node (upper right on output)
	if (std::find(m_closedSet.begin(), m_closedSet.end(), glm::vec2{ nodeCoords.x + 1, nodeCoords.y - 1 }) == m_closedSet.end())
	{
		if (nodeCoords.y - 1 > 0 && nodeCoords.x + 1 < m_field[0].size())
		{
			if (m_field[nodeCoords.y - 1][nodeCoords.x + 1].getf() > 0)
			{
				if (m_field[nodeCoords.y - 1][nodeCoords.x + 1].getf() > 10 * (abs(targetCoords.x - (nodeCoords.x + 1)) + abs(targetCoords.y - (nodeCoords.y - 1))) + nodeg + 14)
				{
					m_field[nodeCoords.y - 1][nodeCoords.x + 1].setg(nodeg + 14);
					m_field[nodeCoords.y - 1][nodeCoords.x + 1].seth(10 * (abs(targetCoords.x - (nodeCoords.x + 1)) + abs(targetCoords.y - (nodeCoords.y - 1))));
					m_field[nodeCoords.y - 1][nodeCoords.x + 1].updatef();
					if (std::find(m_openSet.begin(), m_openSet.end(), glm::vec2{ nodeCoords.x, nodeCoords.y + 1 }) == m_openSet.end())
					{
						m_openSet.push_back(glm::vec2{ nodeCoords.x + 1, nodeCoords.y - 1 });
					}
				}
			}
		}
	}
	//lower left node (upper left on output)
	if (std::find(m_closedSet.begin(), m_closedSet.end(), glm::vec2{ nodeCoords.x - 1, nodeCoords.y - 1 }) == m_closedSet.end())
	{
		if (nodeCoords.y - 1 > 0 && nodeCoords.x - 1 > 0)
		{
			if (m_field[nodeCoords.y - 1][nodeCoords.x - 1].getf() > 0)
			{
				if (m_field[nodeCoords.y - 1][nodeCoords.x - 1].getf() > 10 * (abs(targetCoords.x - (nodeCoords.x - 1)) + abs(targetCoords.y - (nodeCoords.y - 1))) + nodeg + 14)
				{
					m_field[nodeCoords.y - 1][nodeCoords.x - 1].setg(nodeg + 14);
					m_field[nodeCoords.y - 1][nodeCoords.x - 1].seth(10 * (abs(targetCoords.x - (nodeCoords.x - 1)) + abs(targetCoords.y - (nodeCoords.y - 1))));
					m_field[nodeCoords.y - 1][nodeCoords.x - 1].updatef();
					if (std::find(m_openSet.begin(), m_openSet.end(), glm::vec2{ nodeCoords.x - 1, nodeCoords.y - 1 }) == m_openSet.end())
					{
						m_openSet.push_back(glm::vec2{ nodeCoords.x - 1, nodeCoords.y - 1 });
					}
				}
			}
		}
	}

	//removes element from open set by its value
	m_openSet.erase(std::remove(m_openSet.begin(), m_openSet.end(), nodeCoords), m_openSet.end());

	// if not in closed set, puts it there
	if (std::find(m_closedSet.begin(), m_closedSet.end(), nodeCoords) == m_closedSet.end())
	{
		m_closedSet.push_back(nodeCoords);
	}
}

glm::vec2 Pathfinder::getLowestf(std::vector<glm::vec2> openSet)
{
	glm::vec2 lowestfCoords = openSet[0];

	// check all values of open set
	for (int i = 0; i < openSet.size(); i++)
	{
		if (m_field[openSet[i].y][openSet[i].x].getf() <= m_field[lowestfCoords.y][lowestfCoords.x].getf())
		{
			lowestfCoords = openSet[i];
		}
	}

	return lowestfCoords;
}
