#pragma once

#include <glm/glm.hpp>

#include "Solengine/SpriteBatch.h"
#include "Level.h"

const float AGENT_WIDTH = 64.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;
//const int TILE_WIDTH = 64;

class Unit
{
public:
	Unit();
	virtual ~Unit();

	void draw();

	virtual void init(glm::vec2 coords, Solengine::SpriteBatch* spriteBatch) = 0;

	glm::vec2 getPosition() const { return m_position; }	
	glm::vec2 getCoords() const { return m_coords; }
	bool getIsFriendly() const { return m_isFriendly; }

	Solengine::SpriteBatch* getSpriteBatch() { return p_SOL_SB; }

	std::string getName() const { if (m_name == "") return "__"; else return m_name; }
	GLuint getTextureID() const { return m_textureID; }
	
	int getEnergy() { return m_energy; }
	int getEnergyMax() { return m_energyMax; }
	int getHealth() { return m_health; }
	int getHealthMax() { return m_healthMax; }


protected:

	GLuint m_textureID;

	int m_energy;
	int m_energyMax;
	int m_health;
	int m_healthMax;
	bool m_isFriendly;

	std::string m_name;

	Solengine::SpriteBatch* p_SOL_SB;

	glm::vec2 m_position;
	glm::vec2 m_coords;
};

