#include "Pathfinder.h"

#include <iostream>
#include <math.h> 
#include <cmath>
#include <algorithm>

//Better way than redefining here, this is temporary
const float AGENT_WIDTH = 20.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

Pathfinder::Pathfinder()
{
}

Pathfinder::~Pathfinder()
{
}

//Can we sort F by order maybe?
void Pathfinder::pathfind(glm::vec2 startPos, glm::vec2 target)
{
	glm::vec2 startCoords = convertPositionToCoordinates(startPos);
	glm::vec2 targetCoords = convertPositionToCoordinates(target);
	
	//Path is recalculated when either the target coordinates change
	if (m_previousTargetCoords != targetCoords)
	{	
		m_openList.clear();
		m_closedList.clear();
		//reset nodes
		for (int y = 0; y < m_field.size(); y++)
		{
			for (int x = 0; x < m_field[0].size(); x++)
			{
				if (m_field[y][x].m_f >= 0)
				{
					m_field[y][x].m_f = 5000;
					m_field[y][x].m_g = 5000;
					m_field[y][x].m_h = 0;
				}
			}
		}
		//WORK OUR WAY TO START POSITION FROM TARGET

		m_field[targetCoords.y][targetCoords.x].m_g = 0;
		m_field[targetCoords.y][targetCoords.x].m_h = 10 * (abs(targetCoords.x - startCoords.x) + abs(targetCoords.y - startCoords.y));
		m_field[targetCoords.y][targetCoords.x].updatef();
		m_openList.push_back(targetCoords);
		m_field[targetCoords.y][targetCoords.x].p_parent=&m_field[targetCoords.y][targetCoords.x];
		
		glm::vec2 pathCoords = getLowestF();

		while (pathCoords != startCoords)
		{
		    updateNeighbourNodes(pathCoords, startCoords);
		    pathCoords = getLowestF();
		}
	}   
	m_previousTargetCoords = targetCoords;
}

glm::vec2 Pathfinder::getDirectionToNextNode(glm::vec2 startPos)
{
	glm::vec2 startCoords = convertPositionToCoordinates(startPos);

	glm::vec2 parentPos{ m_field[startCoords.y][startCoords.x].p_parent->m_xPos + (0.5f * m_tileWidth), m_field[startCoords.y][startCoords.x].p_parent->m_yPos + (0.5f * m_tileWidth) };

	glm::vec2 dir { 0, 0 };

	glm::vec2 centredStartPos = startPos + glm::vec2{ AGENT_RADIUS, AGENT_RADIUS };

	if (parentPos - centredStartPos != glm::vec2(0, 0))
	{
		dir = glm::normalize(parentPos - centredStartPos);
	}

	return dir;
}

glm::vec2 Pathfinder::convertPositionToCoordinates(glm::vec2 position)
{
	return  { floor((position.x + AGENT_RADIUS) / m_tileWidth), floor((position.y + AGENT_RADIUS) / m_tileWidth) };
}

//We can avoid a lot of repetition here.
void Pathfinder::updateNeighbourNodes(glm::vec2 nodeCoords, glm::vec2 startCoords)
{	 
	for(int i = -1; i <= 1; i++)
	{ 
	    for (int j = -1; j <= 1; j++)
	    {	                                                                                                                                                
	        if (i == 0 && j == 0) continue;                                                                                                                              //base node
			else if (m_field[nodeCoords.y + i][nodeCoords.x + j].m_f < 0) continue;                                                                                      //obstacle node  
            else if (m_field[nodeCoords.y + i][nodeCoords.x].m_f < 0 || m_field[nodeCoords.y][nodeCoords.x + j].m_f < 0) continue;                                       //diagonally impassable  
			else if ((nodeCoords.y + i) >= m_field.size() || (nodeCoords.y + i) < 0 || (nodeCoords.x + j) >= m_field[0].size() || (nodeCoords.x + j) < 0) continue;      //outside of field
			else if (std::find(m_closedList.begin(), m_closedList.end(), glm::vec2{ (nodeCoords.x + j), (nodeCoords.y + i) }) != m_closedList.end()) continue;           //already in closed list
			
			int addedG;                                                                                                                                                  //needed for g value
			if (i == 0 || j == 0) addedG = 10;                                                                                                                           //orthogonal
            else addedG = 14;                                                                                                                                            //diagonally passable

		    updateNode(nodeCoords.x, nodeCoords.y, nodeCoords.x + j, nodeCoords.y + i, startCoords, addedG); 
	    }
	}

	//removes basenode from open set by its value [it's guaranteed to be here]
	m_openList.erase(std::remove(m_openList.begin(), m_openList.end(), nodeCoords), m_openList.end());

	//puts base node in closed set if it's not there already
	if (std::find(m_closedList.begin(), m_closedList.end(), nodeCoords) == m_closedList.end())
	{
		m_closedList.push_back(nodeCoords);
	}
}

void Pathfinder::updateNode(float baseNodeX, float baseNodeY, float updateNodeX, float updateNodeY, glm::vec2 startCoords, int addedG)
{
	float newG = m_field[baseNodeY][baseNodeX].m_g + addedG;

	if (std::find(m_openList.begin(), m_openList.end(), glm::vec2{ updateNodeX, updateNodeY }) == m_openList.end())
	{
			m_openList.push_back(glm::vec2{ updateNodeX, updateNodeY });
			m_field[updateNodeY][updateNodeX].p_parent=&m_field[baseNodeY][baseNodeX];
			m_field[updateNodeY][updateNodeX].m_g = newG;
			m_field[updateNodeY][updateNodeX].m_h = (10 * (abs(startCoords.x - updateNodeX) + abs(startCoords.y - updateNodeY)));
			m_field[updateNodeY][updateNodeX].updatef();
	}
	else
	{
		if (m_field[updateNodeY][updateNodeX].m_g > newG)
		{
			m_field[updateNodeY][updateNodeX].p_parent=&m_field[baseNodeY][baseNodeX];
			m_field[updateNodeY][updateNodeX].m_g = newG;
			m_field[updateNodeY][updateNodeX].updatef();
		}
	}	
}

glm::vec2 Pathfinder::getLowestF()
{
	glm::vec2 lowestFCoords = m_openList[0];
	// check all values of open set
	for (int i = 0; i < m_openList.size(); i++)
	{
		//prioritises later added members of the set, storing lowest coordinates with lowest f value
		if (m_field[m_openList[i].y][m_openList[i].x].m_f <= m_field[lowestFCoords.y][lowestFCoords.x].m_f)
		{
			lowestFCoords = m_openList[i];
		}
	}
	return lowestFCoords;
}
