#include "Level.h"

#include "Solengine/ErrorHandler.h"
#include "Solengine/ResourceManager.h"

#include <fstream>
#include <iostream>

Level::Level(std::vector<std::string> levelData, Solengine::SpriteBatch* batch)
{
	p_SOL_SB = batch;
	batch->begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	Solengine::ColourRGBA8 whiteColour = { 255, 255, 255, 255 };
	Solengine::ColourRGBA8 tileColour = { 100, 100, 100, 255 };

	std::vector<std::vector<Tile*>> tileMap;

	//Render tiles
	for (size_t y = 0; y < levelData.size(); y++)
	{
		std::vector<Tile*> tileRow;

		for (unsigned int x = 0; x < levelData[y].size(); x++)
		{
			char tile = levelData[y][x];

            glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, 
				               TILE_WIDTH, TILE_WIDTH);

			//Process tile
			switch (tile)
			{
			case 'X':
				batch->draw(destRect, uvRect, 
					        Solengine::ResourceManager::getTexture(
						    "Textures/zombie_pack/light_bricks.png").textureID, 
					        0.0f, whiteColour);
				tileRow.push_back(new Tile(true, false, x, y, TILE_WIDTH));
				break;
			case '.':
                batch->draw(destRect, uvRect, 
					        Solengine::ResourceManager::getTexture(
                            "Textures/zombie_pack/DQtile.png").textureID, 
					        0.0f, tileColour);
				tileRow.push_back(new Tile(false, false, x, y, TILE_WIDTH));
				break;
			case 'A':
				batch->draw(destRect, uvRect, 
					        Solengine::ResourceManager::getTexture(
						   "Textures/zombie_pack/DQtile.png").textureID, 
					        0.0f, tileColour);
				tileRow.push_back(new Tile(false, true, x, y, TILE_WIDTH));
				m_adeptSpawnCoords = glm::vec2{ x , y };
				break;
			case 'F':
				batch->draw(destRect, uvRect, 
					        Solengine::ResourceManager::getTexture(
					        "Textures/zombie_pack/DQtile.png").textureID, 
					        0.0f, tileColour);
				tileRow.push_back(new Tile(false, true, x, y, TILE_WIDTH));
				m_fighterSpawnCoords = glm::vec2{ x , y };
				break;
			case 'S':
				batch->draw(destRect, uvRect, 
					        Solengine::ResourceManager::getTexture(
							"Textures/zombie_pack/DQtile.png").textureID, 
					        0.0f, tileColour);
				tileRow.push_back(new Tile(false, true, x, y, TILE_WIDTH));
				m_scoutSpawnCoords = glm::vec2{ x , y };
				break;
			case 'R':
				batch->draw(destRect, uvRect, 
					        Solengine::ResourceManager::getTexture(
							"Textures/zombie_pack/DQtile.png").textureID, 
					        0.0f, tileColour);
				tileRow.push_back(new Tile(false, true, x, y, TILE_WIDTH));
				m_ratSpawnCoords = glm::vec2{ x , y };
				break;
			default:

				break;
			}
		}

		if (tileRow.size() > 0) tileMap.push_back(tileRow);
	}
	batch->end();

	//set neighbours

	for (size_t y = 0; y < tileMap.size(); y++)
		for (size_t x = 0; x < tileMap[0].size(); x++)
			if (!tileMap[y][x]->m_isObstacle)
			{
				if (y > 0)
					if (!tileMap[y - 1][x]->m_isObstacle)
                        tileMap[y][x]->addNeighbour(tileMap[y - 1][x]);

				if (y < tileMap.size() - 1)
					if (!tileMap[y + 1][x]->m_isObstacle)
						tileMap[y][x]->addNeighbour(tileMap[y + 1][x]);

				if (x > 0)
					if (!tileMap[y][x - 1]->m_isObstacle)
						tileMap[y][x]->addNeighbour(tileMap[y][x - 1]);

				if (x < tileMap[0].size() - 1)
					if (!tileMap[y][x + 1]->m_isObstacle)
						tileMap[y][x]->addNeighbour(tileMap[y][x + 1]);
			}

	m_tileMap.init(tileMap, TILE_WIDTH);
}

Level::~Level()
{
}

void Level::draw()
{
	p_SOL_SB->renderBatch();
}