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

//Can we sort F by order maybe?
void Pathfinder::pathfind(glm::vec2 startPos, glm::vec2 target)
{
	glm::vec2 startCoords = convertPositionToCoordinates(startPos);
	glm::vec2 targetCoords = convertPositionToCoordinates(target);
	
	//Path is recalculated when either the target coordinates or the start coordinates change
	if (m_previousTargetCoords != targetCoords)
	{	
		m_openSet.clear();
		m_closedSet.clear();
		//reset nodes
		for (int y = 0; y < m_field.size(); y++)
		{
			for (int x = 0; x < m_field[0].size(); x++)
			{
				if (m_field[y][x].getf() >= 0)
				{
					m_field[y][x].setf(5000);
					m_field[y][x].setg(5000);
					m_field[y][x].seth(0);
				}
			}
		}
		//WORK OUR WAY TO START POSITION FROM TARGET

		m_field[targetCoords.y][targetCoords.x].setg(0);
		m_field[targetCoords.y][targetCoords.x].seth(10 * (abs(targetCoords.x - startCoords.x) + abs(targetCoords.y - startCoords.y)));
		m_field[targetCoords.y][targetCoords.x].updatef();
		m_openSet.push_back(targetCoords);
		m_field[targetCoords.y][targetCoords.x].setParent(&m_field[targetCoords.y][targetCoords.x]);
		
		glm::vec2 pathCoords = getLowestf();

		while (pathCoords != startCoords)
		{
		    updateNeighbourNodes(pathCoords, startCoords);
		    pathCoords = getLowestf();
		}
		//The path should go from each square to its parent until you reach the starting square. This is the path.
		
		//announce map
		/*
		for (int y = 0; y < m_field.size(); y++)
		{
			for (int x = 0; x < m_field[0].size(); x++)
			{
				if (m_field[y][x].getf() < 0)
				{
					std::cout << "x";
				}
				else if (m_field[y][x].getXCoord() == targetCoords.x && m_field[y][x].getYCoord() == targetCoords.y)
				{
					std::cout << "T";
				}
				else if (m_field[y][x].getf() == 5000)
				{
					std::cout << "_";
					
				}
				else if (std::find(m_closedSet.begin(), m_closedSet.end(), glm::vec2{ m_field[y][x].getXCoord(), m_field[y][x].getYCoord() }) != m_closedSet.end())
				{
					std::cout << m_field[y][x].getDir();
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
		*/
	}   

	m_previousTargetCoords = targetCoords;
}

glm::vec2 Pathfinder::getDirectionToNextNode(glm::vec2 startPos)
{
	glm::vec2 startCoords = convertPositionToCoordinates(startPos);

	//The direction we're getting from this is doing weird things.
	glm::vec2 dir = m_field[startCoords.y][startCoords.x].getDirectionToParent(startPos + glm::vec2{ AGENT_RADIUS, AGENT_RADIUS });

	return dir;
}

glm::vec2 Pathfinder::convertPositionToCoordinates(glm::vec2 position)
{
	glm::vec2 coordinates;

	coordinates.x = floor((position.x + AGENT_RADIUS) / m_tileWidth);
	coordinates.y = floor((position.y + AGENT_RADIUS) / m_tileWidth);

	return coordinates;
}

//We can avoid a lot of repetition here.
void Pathfinder::updateNeighbourNodes(glm::vec2 nodeCoords, glm::vec2 startCoords)
{	
	//updates neighbouring nodes
	updateNode(nodeCoords.x, nodeCoords.y, nodeCoords.x, nodeCoords.y  + 1, startCoords, false);
	updateNode(nodeCoords.x, nodeCoords.y, nodeCoords.x, nodeCoords.y - 1, startCoords, false);
	updateNode(nodeCoords.x, nodeCoords.y, nodeCoords.x + 1, nodeCoords.y, startCoords, false);
	updateNode(nodeCoords.x, nodeCoords.y, nodeCoords.x - 1, nodeCoords.y, startCoords, false);
	//if walkable
	if (m_field[nodeCoords.y + 1][nodeCoords.x].getf() >= 0 && m_field[nodeCoords.y][nodeCoords.x + 1].getf()) 
	{
		updateNode(nodeCoords.x, nodeCoords.y, nodeCoords.x + 1, nodeCoords.y + 1, startCoords, true);
	}
	if (m_field[nodeCoords.y + 1][nodeCoords.x].getf() >= 0 && m_field[nodeCoords.y][nodeCoords.x - 1].getf() >= 0)
	{
		updateNode(nodeCoords.x, nodeCoords.y, nodeCoords.x - 1, nodeCoords.y + 1, startCoords, true);
	}
	if (m_field[nodeCoords.y - 1][nodeCoords.x].getf() >= 0 && m_field[nodeCoords.y][nodeCoords.x + 1].getf() >= 0)
	{
	    updateNode(nodeCoords.x, nodeCoords.y, nodeCoords.x + 1, nodeCoords.y - 1, startCoords, true);
	}
	if (m_field[nodeCoords.y - 1][nodeCoords.x].getf() >= 0 && m_field[nodeCoords.y][nodeCoords.x - 1].getf() >= 0)
	{
	    updateNode(nodeCoords.x, nodeCoords.y, nodeCoords.x - 1, nodeCoords.y - 1, startCoords, true);
	}

	//removes basenode from open set by its value [it's guaranteed to be here]
	m_openSet.erase(std::remove(m_openSet.begin(), m_openSet.end(), nodeCoords), m_openSet.end());

	//puts base node in closed set if it's not there already
	if (std::find(m_closedSet.begin(), m_closedSet.end(), nodeCoords) == m_closedSet.end())
	{
		m_closedSet.push_back(nodeCoords);
	}
}

void Pathfinder::updateNode(float baseNodeX, float baseNodeY, float updateNodeX, float updateNodeY, glm::vec2 startCoords, bool isDiag)
{
	//NTS -- only change nodeg if it is an improvement??
	float nodeg = m_field[baseNodeY][baseNodeX].getg();
	
	//NTS -- could we organise this for optimisation??
	//update only if update node isn't in closed set
	if (std::find(m_closedSet.begin(), m_closedSet.end(), glm::vec2{ updateNodeX, updateNodeY }) == m_closedSet.end())
	{
		//update only if update node is within node field
		if (updateNodeY < m_field.size() && updateNodeY >= 0 && updateNodeX < m_field[0].size() && updateNodeX >= 0)
		{
			//update only if update node's f value > 0 (f is -1 for impassable nodes)
			if (m_field[updateNodeY][updateNodeX].getf() > 0)
			{
				if (isDiag) nodeg += 4;
				// check if update node is on open list
				// if not: add it, set base node as its parent, set its g and record its f
				// if it is: check its g cost. if we lower its g cost here, set base node as its parent, set its g and record its f
				if (std::find(m_openSet.begin(), m_openSet.end(), glm::vec2{ updateNodeX, updateNodeY }) == m_openSet.end())
				{
					m_openSet.push_back(glm::vec2{ updateNodeX, updateNodeY });
					m_field[updateNodeY][updateNodeX].setParent(&m_field[baseNodeY][baseNodeX]);
					m_field[updateNodeY][updateNodeX].setg(nodeg + 10);
					m_field[updateNodeY][updateNodeX].seth(10 * (abs(startCoords.x - updateNodeX) + abs(startCoords.y - updateNodeY)));
					m_field[updateNodeY][updateNodeX].updatef();
				}
				else
				{
					if (m_field[updateNodeY][updateNodeX].getg() > nodeg + 10)
					{
						m_field[updateNodeY][updateNodeX].setParent(&m_field[baseNodeY][baseNodeX]);
						m_field[updateNodeY][updateNodeX].setg(nodeg + 10);
						m_field[updateNodeY][updateNodeX].updatef();
					}
				}
			}
		}
	}
}

glm::vec2 Pathfinder::getLowestf()
{
	glm::vec2 lowestfCoords = m_openSet[0];
	// check all values of open set
	for (int i = 0; i < m_openSet.size(); i++)
	{
		//prioritises later added members of the set, storing lowest coordinates with lowest f value
		if (m_field[m_openSet[i].y][m_openSet[i].x].getf() <= m_field[lowestfCoords.y][lowestfCoords.x].getf())
		{
			lowestfCoords = m_openSet[i];
		}
	}
	return lowestfCoords;
}
