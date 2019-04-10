#include "Level.h"

#include <fstream>
#include <iostream>

#include "Solengine/ErrorHandler.h"
#include "Solengine/ResourceManager.h"

Level::Level(std::vector<std::string> levelData, Solengine::SpriteBatch* spriteBatch)
{
	p_SOL_SB = spriteBatch;
	spriteBatch->begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	Solengine::ColourRGBA8 whiteColour = {/*r*/ 255, /*g*/ 255, /*b*/ 255, /*a*/ 255 };
	Solengine::ColourRGBA8 tileColour = {/*r*/ 100, /*g*/ 100, /*b*/ 100, /*a*/ 255 };

	std::vector<std::vector<Tile*>> tileMap;

	//Render tiles
	for (unsigned int y = 0; y < levelData.size(); y++)
	{
		std::vector<Tile*> tileRow;

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
				tileRow.push_back(new Tile(true, false, x, y, TILE_WIDTH));
				break;
			case '.':
				spriteBatch->draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID, 0.0f, tileColour);
				tileRow.push_back(new Tile(false, false, x, y, TILE_WIDTH));
				break;
			case 'A':
				spriteBatch->draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID, 0.0f, tileColour);
				tileRow.push_back(new Tile(false, true, x, y, TILE_WIDTH));
				m_adeptSpawnCoords = glm::vec2{ x , y };
				break;
			case 'F':
				spriteBatch->draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID, 0.0f, tileColour);
				tileRow.push_back(new Tile(false, true, x, y, TILE_WIDTH));
				m_fighterSpawnCoords = glm::vec2{ x , y };
				break;
			case 'S':
				spriteBatch->draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID, 0.0f, tileColour);
				tileRow.push_back(new Tile(false, true, x, y, TILE_WIDTH));
				m_scoutSpawnCoords = glm::vec2{ x , y };
				break;
			case 'R':
				spriteBatch->draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/DQtile.png").textureID, 0.0f, tileColour);
				tileRow.push_back(new Tile(false, true, x, y, TILE_WIDTH));
				m_ratSpawnCoords = glm::vec2{ x , y };
				break;
			default:

				break;
			}
		}

		if (tileRow.size() > 0) tileMap.push_back(tileRow);
	}
	spriteBatch->end();

	//set neighbours

	for (size_t y = 0; y < tileMap.size(); y++)
	{
		for (size_t x = 0; x < tileMap[0].size(); x++)
		{
			if (y > 0) tileMap[y][x]->addNeighbour(tileMap[y - 1][x]);
			if (y < tileMap.size() - 1) tileMap[y][x]->addNeighbour(tileMap[y + 1][x]);
			if (x > 0) tileMap[y][x]->addNeighbour(tileMap[y][x - 1]);
			if (x < tileMap[0].size() - 1) tileMap[y][x]->addNeighbour(tileMap[y][x + 1]);

		}
	}

	m_tileMap.init(tileMap, TILE_WIDTH);

	for (size_t y = 0; y < m_tileMap.p_tiles.size(); y++)
	{
		for (size_t x = 0; x < m_tileMap.p_tiles[0].size(); x++)
		{
			std::cout << m_tileMap.p_tiles[y][x]->p_neighbours.size();
		}

		std::cout << std::endl;
	}

}

Level::~Level()
{

}
