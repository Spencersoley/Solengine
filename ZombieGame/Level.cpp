#include "Level.h"

#include <fstream>
#include <iostream>

#include "Solengine/ErrorHandler.h"
#include "Solengine/ResourceManager.h"

Level::Level(std::vector<std::string> levelData)
{
	m_levelData = levelData;
	m_SOL_levelSpriteBatch.init();
	m_SOL_levelSpriteBatch.begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	Solengine::ColourRGBA8 whiteColour = {/*r*/ 255, /*g*/ 255, /*b*/ 255, /*a*/ 255 };

	//Render tiles
	//Whenever we load in a level, we need to set the agent symbols back to a dot
	for (unsigned int y = 0; y < levelData.size(); y++)
	{
		std::vector<Node> m_nodeRow;

		for (unsigned int x = 0; x < levelData[y].size(); x++) 
		{
			//Grab tile
			char tile = levelData[y][x];

			//Gives the tile a position to be drawn
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			//Process tile
			switch (tile) 
			{
			    case 'R':
					m_SOL_levelSpriteBatch.draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/light_bricks.png").textureID, 0.0f, whiteColour);
					//std::cout << x << " " << y << std::endl;
					m_nodeRow.emplace_back(-1, x, y, TILE_WIDTH);
					break;
				case 'G':
					m_SOL_levelSpriteBatch.draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/glass.png").textureID, 0.0f, whiteColour);
					//std::cout << x << " " << y << std::endl;
					m_nodeRow.emplace_back(-1, x, y, TILE_WIDTH);
					break;
				case 'L':
				    m_SOL_levelSpriteBatch.draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/light_bricks.png").textureID, 0.0f, whiteColour);
					//std::cout << x << " " << y << std::endl;
					m_nodeRow.emplace_back(-1, x, y, TILE_WIDTH);
					break;
				case '@':
					//std::cout << x << " " << y << std::endl;
					m_levelData[y][x] = '.';
					m_startPlayerPosition.x = (float)(x * TILE_WIDTH);
					m_startPlayerPosition.y = (float)(y * TILE_WIDTH);
					m_nodeRow.emplace_back(5000, x, y, TILE_WIDTH);
					break;
				case 'Z':
					//std::cout << x << " " << y << std::endl;
					m_levelData[y][x] = '.';
					m_startZombiePositions.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
					m_nodeRow.emplace_back(5000, x, y, TILE_WIDTH);
					break;
				case '.':
					//std::cout << x << " " << y << std::endl;
					m_nodeRow.emplace_back(5000, x, y, TILE_WIDTH);
					break;
				default: 
					//std::cout << "Unexpected symbol " << tile << "at " << x << "," << y;
					m_nodeRow.emplace_back(-1, x, y, TILE_WIDTH);
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

