#pragma once

#include <string>
#include <vector>

#include <Solengine/SpriteBatch.h>

const int TILE_WIDTH = 64;

class Level
{
public:
	//Load the level
	//Const is so it is a constant reference to a string and not a copy
	Level(const std::string& fileName);
	~Level();

	void draw();

	//Getters
	int getWidth() const { return _levelData[0].size(); } //nts: It's a vector of strings. Width is the size of the string, height is the number of strings
	int getHeight() const { return _levelData.size(); }
	int getNumHumans() const { return _numHumans; }
	glm::vec2 getStartPlayerPosition() const { return _startPlayerPosition; }
	const std::vector<glm::vec2>& getStartZombiePositions() const { return _startZombiePositions; }
	const std::vector<std::string>& getLevelData() const { return _levelData; }

private:
	std::vector<std::string> _levelData;
	int _numHumans;
	Solengine::SpriteBatch _spriteBatch;

	glm::vec2 _startPlayerPosition;
	std::vector<glm::vec2> _startZombiePositions;
};

//Render a texture for each tile
//Usually using SpriteBatch we call begin and end every frame.
//However, the level data only gets loaded in a single time 
//we can render it to the screen without having to recreate it.
