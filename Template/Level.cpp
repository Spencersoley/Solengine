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
	for (unsigned int y = 0; y < levelData.size(); y++)
	{
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
				//m_SOL_levelSpriteBatch.draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/light_bricks.png").textureID, 0.0f, whiteColour);

				break;
			default:

				break;
			}
		}
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

