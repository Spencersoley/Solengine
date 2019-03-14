#include "Level.h"

#include <fstream>
#include <iostream>

#include "Solengine/ErrorHandler.h"
#include "Solengine/ResourceManager.h"

Level::Level(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName);

	if (file.fail())
	{
		Solengine::fatalError(fileName + "would not open");
	}

	//Throw away the first string in temp
	std::string temp;
	file >> temp >> m_numHumans;

	std::getline(file, temp);

	//Will read each line one by one and put it in temp
	while (std::getline(file, temp))
	{
		m_levelData.push_back(temp);
	}

	m_SOL_levelSpriteBatch.init();
	m_SOL_levelSpriteBatch.begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	Solengine::ColourRGBA8 whiteColour = {/*r*/ 255, /*g*/ 255, /*b*/ 255, /*a*/ 255 };

	//Render tiles
	//Whenever we load in a level, we need to set the agent symbols back to a dot
	for (unsigned int y = 0; y < m_levelData.size(); y++)
	{
		std::vector<Node> m_nodeRow;

		for (unsigned int x = 0; x < m_levelData[y].size(); x++) 
		{
			//Grab tile
			char tile = m_levelData[y][x];

			//Get destination rect
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			//Process tile
			switch (tile) 
			{
			    case 'R':
					m_SOL_levelSpriteBatch.draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/light_bricks.png").textureID, 0.0f, whiteColour);
					std::cout << 'R' << Solengine::ResourceManager::getTexture("Textures/zombie_pack/light_bricks.png").textureID << "\n";
					m_nodeRow.emplace_back(-1, x, y);
					break;
				case 'G':
					m_SOL_levelSpriteBatch.draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/glass.png").textureID, 0.0f, whiteColour);
					std::cout << 'G' << Solengine::ResourceManager::getTexture("Textures/zombie_pack/glass.png").textureID << "\n";
					m_nodeRow.emplace_back(-1, x, y);
					break;
				case 'L':
				    m_SOL_levelSpriteBatch.draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/light_bricks.png").textureID, 0.0f, whiteColour);
					std::cout << 'L' << Solengine::ResourceManager::getTexture("Textures/zombie_pack/light_bricks.png").textureID << "\n";
					m_nodeRow.emplace_back(-1, x, y);
					break;
				case '@':
					std::cout << '@' << "\n";
					m_levelData[y][x] = '.';
					m_startPlayerPosition.x = (float)(x * TILE_WIDTH);
					m_startPlayerPosition.y = (float)(y * TILE_WIDTH);
					m_nodeRow.emplace_back(5000, x, y);
					break;
				case 'Z':
					std::cout << 'Z' << "\n";
					m_levelData[y][x] = '.';
					m_startZombiePositions.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
					m_nodeRow.emplace_back(5000, x, y);
					break;
				case '.':
					m_nodeRow.emplace_back(5000, x, y);
					break;
				default: 
					std::cout << "Unexpected symbol " << tile << "at " << x << "," << y;
					m_nodeRow.emplace_back(-1, x, y);
					break;
			}
		}

		m_nodeField.push_back(m_nodeRow);
	}

	m_SOL_levelSpriteBatch.end();
}

Level::~Level()
{
}

void Level::draw() 
{
	m_SOL_levelSpriteBatch.renderBatch();
}

void Level::nodeCheck()
{
	for (unsigned int y = 0; y < m_nodeField.size(); y++) 
	{
		for (unsigned int x = 0; x < m_nodeField[y].size(); x++)
		{
			std::cout << m_nodeField[y][x].getYPos();
		}
		std::cout << std::endl;
	}	
}