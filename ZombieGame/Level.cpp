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
	file >> temp >> _numHumans;

	std::getline(file, temp);

	//Will read each line one by one and put it in temp
	while (std::getline(file, temp))
	{
		_levelData.push_back(temp);
	}

	_spriteBatch.init();
	_spriteBatch.begin();


	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	Solengine::ColourRGBA8 whiteColour = {/*r*/ 255, /*g*/ 255, /*b*/ 255, /*a*/ 255 };

	//Render tiles
	//Whenever we load in a level, we need to set the agent symbols back to a dot
	for (unsigned int y = 0; y < _levelData.size(); y++)
	{
		for (unsigned int x = 0; x < _levelData[y].size(); x++) 
		{
			//Grab tile
			char tile = _levelData[y][x];

			//Get destination rect
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			//Process tile
			switch (tile) 
			{
			    case 'R':
					_spriteBatch.draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/light_bricks.png").textureID, 0.0f, whiteColour);
					std::cout << 'R' << Solengine::ResourceManager::getTexture("Textures/zombie_pack/light_bricks.png").textureID << "\n";
					break;
				case 'G':
					_spriteBatch.draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/glass.png").textureID, 0.0f, whiteColour);
					std::cout << 'G' << Solengine::ResourceManager::getTexture("Textures/zombie_pack/glass.png").textureID << "\n";
					break;
				case 'L':
				    _spriteBatch.draw(destRect, uvRect, Solengine::ResourceManager::getTexture("Textures/zombie_pack/light_bricks.png").textureID, 0.0f, whiteColour);
					std::cout << 'L' << Solengine::ResourceManager::getTexture("Textures/zombie_pack/light_bricks.png").textureID << "\n";
					break;
				case '@':
					std::cout << '@' << "\n";
					_levelData[y][x] = '.';
					_startPlayerPosition.x = (float)(x * TILE_WIDTH);
					_startPlayerPosition.y = (float)(y * TILE_WIDTH);
					break;
				case 'Z':
					std::cout << 'Z' << "\n";
					_levelData[y][x] = '.';
					_startZombiePositions.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
					break;
				case '.':
					break;
				default: 
					std::cout << "Unexpected symbol " << tile << "at " << x << "," << y;
					break;
			}
		}
	}


	_spriteBatch.end();
}

Level::~Level()
{
}

void Level::draw() 
{
	_spriteBatch.renderBatch();
}