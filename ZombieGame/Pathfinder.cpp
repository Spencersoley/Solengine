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

glm::vec2 Pathfinder::pathfind(glm::vec2 startPos, glm::vec2 target)
{
	glm::vec2 dir = { 0, 0 };
	glm::vec2 targetCoords = converPositionToCoordinates(target);
	glm::vec2 startCoords = converPositionToCoordinates(startPos);

	if (m_previousTargetCoords != targetCoords)
	{	
		m_openSet.clear();
		m_closedSet.clear();
		
		m_field[startCoords.y][startCoords.x].setg(0);
		m_field[startCoords.y][startCoords.x].seth(10 * (abs(targetCoords.x - startCoords.x) + abs(targetCoords.y - startCoords.y)));
		m_field[startCoords.y][startCoords.x].updatef();
		m_field[startCoords.y][startCoords.x].setParent(&m_field[startCoords.y][startCoords.x]);
		m_openSet.push_back(startCoords);
		
		glm::vec2 pathCoords = startCoords;
		//creates a path following the lowest f value
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
	}   

	m_previousTargetCoords = targetCoords;

	dir = glm::vec2 { 0, 0 }; //m_field[startCoords.y][startCoords.x].getDir();
	return dir;
}

glm::vec2 Pathfinder::converPositionToCoordinates(glm::vec2 position)
{
	glm::vec2 coordinates;

	coordinates.x = floor((position.x + AGENT_RADIUS) / m_tileWidth);
	coordinates.y = floor((position.y + AGENT_RADIUS) / m_tileWidth);

	return coordinates;
}

//We can avoid a lot of repetition here.
void Pathfinder::updateNeighbourNodes(glm::vec2 nodeCoords, glm::vec2 targetCoords)
{	
	//updates neighbouring nodes
	updateNode(nodeCoords.x, nodeCoords.y, nodeCoords.x, nodeCoords.y  + 1, targetCoords, false);
	updateNode(nodeCoords.x, nodeCoords.y, nodeCoords.x, nodeCoords.y - 1, targetCoords, false);
	updateNode(nodeCoords.x, nodeCoords.y, nodeCoords.x + 1, nodeCoords.y, targetCoords, false);
	updateNode(nodeCoords.x, nodeCoords.y, nodeCoords.x - 1, nodeCoords.y, targetCoords, false);
	updateNode(nodeCoords.x, nodeCoords.y, nodeCoords.x + 1, nodeCoords.y + 1, targetCoords, true);
	updateNode(nodeCoords.x, nodeCoords.y, nodeCoords.x - 1, nodeCoords.y + 1, targetCoords, true);
	updateNode(nodeCoords.x, nodeCoords.y, nodeCoords.x + 1, nodeCoords.y - 1, targetCoords, true);
	updateNode(nodeCoords.x, nodeCoords.y, nodeCoords.x - 1, nodeCoords.y - 1, targetCoords, true);

	//removes basenode from open set by its value
	m_openSet.erase(std::remove(m_openSet.begin(), m_openSet.end(), nodeCoords), m_openSet.end());

	//puts base node in closed set if it's not there already
	if (std::find(m_closedSet.begin(), m_closedSet.end(), nodeCoords) == m_closedSet.end())
	{
		m_closedSet.push_back(nodeCoords);
	}
}

void Pathfinder::updateNode(float baseNodeX, float baseNodeY, float updateNodeX, float updateNodeY, glm::vec2 targetCoords, bool isDiag)
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
				//nodeg needs to be greater for diagonal tiles
				if (isDiag) nodeg + 4;
				//update only if it will lower the g value
				if (m_field[updateNodeY][updateNodeX].getg() > nodeg + 10)
				{
					//set update node's g value based on base node's g value 
					m_field[updateNodeY][updateNodeX].setg(nodeg + 10);
					//set update node's h value based on number of non diagonal tiles from the target
					m_field[updateNodeY][updateNodeX].seth(10 * (abs(targetCoords.x - updateNodeX) + abs(targetCoords.y - updateNodeY)));
					//updates the update node's f value based on its new g and h values
					m_field[updateNodeY][updateNodeX].updatef();
					//checks if the update node is in the open set  				
					if (std::find(m_openSet.begin(), m_openSet.end(), glm::vec2{ updateNodeX, updateNodeY }) == m_openSet.end())
					{
						//if it's not in the open set, it is added to it
						m_openSet.push_back(glm::vec2{ updateNodeX, updateNodeY });
						//set update node's parent as the base node (by reference)
						m_field[updateNodeY][updateNodeX].setParent(&m_field[baseNodeY][baseNodeX]);
					}
					else
					{
						//set's update node's parent as the base node (by reference)
						m_field[updateNodeY][updateNodeX].setParent(&m_field[baseNodeY][baseNodeX]);
					}
				}
			}
		}
	}
}

glm::vec2 Pathfinder::getLowestf(std::vector<glm::vec2> openSet)
{
	glm::vec2 lowestfCoords = openSet[0];
	// check all values of open set
	for (int i = 0; i < openSet.size(); i++)
	{
		//prioritises later added members of the set, storing lowest coordinates with lowest f value
		if (m_field[openSet[i].y][openSet[i].x].getf() <= m_field[lowestfCoords.y][lowestfCoords.x].getf())
		{
			lowestfCoords = openSet[i];
		}
	}
	return lowestfCoords;
}
