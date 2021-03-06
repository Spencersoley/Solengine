#pragma once

#include <string>
#include <vector>

#include <Solengine/SpriteBatch.h>

#include "Node.h"

const int TILE_WIDTH = 64;

class Level
{
public:
	//Load the level
	Level(std::vector<std::string> levelData);
	~Level();

	void draw();

	int getWidth() const { return m_levelData[0].size(); } //nts: It's a vector of strings. Width is the size of the string, height is the number of strings
	int getHeight() const { return m_levelData.size(); }
	glm::vec2 getStartPlayerPosition() const { return m_startPlayerPosition; }
	const std::vector<glm::vec2>& getStartZombiePositions() const { return m_startZombiePositions; }
	const std::vector<std::string>& getLevelData() const { return m_levelData; }

	std::vector<std::vector<Node>> getNodeField() { return m_nodeField; }

private:
	std::vector<std::string> m_levelData;
	std::vector<std::vector<Node>> m_nodeField;

	Solengine::SpriteBatch m_SOL_levelSpriteBatch;
	glm::vec2 m_startPlayerPosition;
	std::vector<glm::vec2> m_startZombiePositions;
};


//Render a texture for each tile
//Usually using SpriteBatch we call begin and end every frame.
//However, the level data only gets loaded in a single time 
//we can render it to the screen without having to recreate it.
