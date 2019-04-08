#include "Level.h"

#include <fstream>
#include <iostream>

#include "Solengine/ErrorHandler.h"
#include "Solengine/ResourceManager.h"

Level::Level(std::vector<std::string> levelData, Solengine::SpriteBatch* spriteBatch)
{
	m_levelData = levelData;
	p_SOL_SB = spriteBatch;

	spriteBatch->begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	Solengine::ColourRGBA8 whiteColour = {/*r*/ 255, /*g*/ 255, /*b*/ 255, /*a*/ 255 };

	//Render tiles
	for (unsigned int y = 0; y < levelData.size(); y++)
	{
		std::vector<Tile> tileRow;

		for (unsigned int x = 0; x < levelData[y].size(); x++)
		{
			//Grab tile
			char tile = levelData[y][x];

			//Gives the tile a position to be drawn
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			//Process tile
			switch (tile)
			{
			case 'X':
				spriteBatch->draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/light_bricks.png").textureID, 0.0f, whiteColour);
				tileRow.emplace_back(true, x, y, TILE_WIDTH);
				break;
			case '.':
				spriteBatch->draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID, 0.0f, whiteColour);
				tileRow.emplace_back(false, x, y, TILE_WIDTH);
				break;
			case 'A':
				spriteBatch->draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID, 0.0f, whiteColour);
				tileRow.emplace_back(false, x, y, TILE_WIDTH);		
				m_adeptSpawnCoords = glm::vec2{ x , y };
				break;
			case 'F':
				spriteBatch->draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID, 0.0f, whiteColour);
				tileRow.emplace_back(false, x, y, TILE_WIDTH);
				m_fighterSpawnCoords = glm::vec2{ x , y };
				break;
			case 'S':
				spriteBatch->draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID, 0.0f, whiteColour);
				tileRow.emplace_back(false, x, y, TILE_WIDTH);
				m_scoutSpawnCoords = glm::vec2{ x , y };
				break;
			case 'R':
				spriteBatch->draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID, 0.0f, whiteColour);
				tileRow.emplace_back(false, x, y, TILE_WIDTH);
				m_ratSpawnCoords = glm::vec2{ x , y };
				break;
			default:

				break;
			}
		}

		if (tileRow.size() > 0) m_tileMap.push_back(tileRow);
	}
	spriteBatch->end();

	for (size_t y = 0; y < m_tileMap.size(); y++)
	{
		for (size_t x = 0; x < m_tileMap[0].size(); x++)
		{
			if (m_tileMap[y][x].m_obstacle) std::cout << "R";
			else std::cout << ".";
		}
		std::cout << std::endl;
	}
}

Level::~Level()
{
}
