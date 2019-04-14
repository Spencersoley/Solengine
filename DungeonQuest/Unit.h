#pragma once

#include <glm/glm.hpp>

#include "Solengine/SpriteBatch.h"
#include "Level.h"
#include "Drawable.h"

const float AGENT_WIDTH = 64.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;
//const int TILE_WIDTH = 64;

class Unit : public Drawable
{
public:
	Unit();
	virtual ~Unit();

	void init(glm::vec2 coords, Solengine::SpriteBatch* spriteBatch);

	glm::vec2 getCoords() const { return { floor(m_pos.x / TILE_WIDTH), floor(m_pos.y / TILE_WIDTH) }; }
	bool getIsFriendly() const { return m_isFriendly; }

	std::string getName() const { if (m_name == "") return "__"; else return m_name; }
	
	int getEnergy() { return m_energy; }
	int getEnergyMax() { return m_energyMax; }
	int getHealth() { return m_health; }
	int getHealthMax() { return m_healthMax; }

	void resetEnergy() { m_energy = m_energyMax; }
	void removeEnergy(int energyUsed) { m_energy -= energyUsed; }

	void newTurn() { m_energy = m_energyMax; }


protected:

	int m_energy;
	int m_energyMax;
	int m_health;
	int m_healthMax;
	bool m_isFriendly;
	std::string m_name;
};