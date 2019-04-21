#pragma once

#include <Solengine/SpriteBatch.h>

#include <glm/glm.hpp>

#include "Level.h"
#include "Drawable.h"
#include "MoveSet.h"
#include "UIIcon.h"

const float AGENT_WIDTH = 64.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

class Unit : public Drawable
{
public:
	Unit();
	virtual ~Unit();

	void init(glm::ivec2 coords, Solengine::SpriteBatch* spriteBatch);

    glm::ivec2 getCoords() const 
	{ 
        return { floor(m_pos.x / TILE_WIDTH), floor(m_pos.y / TILE_WIDTH) }; 
	}

	bool getIsFriendly() const { return m_isFriendly; }
    int getMoveCost() { return m_movementCost; }

	std::string getName() const 
	{ 
        if (m_name == "") return "__";
		else return m_name;
	}
	
	int getEnergy() { return m_energy; }
	int getEnergyMax() { return m_energyMax; }
	int getHealth() { return m_health; }
	int getHealthMax() { return m_healthMax; }

	void setEnergy(int nrg) { m_energy = nrg; }

	void resetEnergy() { m_energy = m_energyMax; }
	void removeEnergy(int energyUsed) { m_energy -= energyUsed; }

	void removeHealth(int dmg) { m_health -= dmg; }

	void newTurn() { m_energy = m_energyMax; }

	MoveSet m_moveSet;

	void setHealthbar(UIIcon* hb, UIIcon* hbb)
	{
		p_healthbar = hb;
		p_healthbarBackplate = hbb;
	}

	void updateHealthbar() 
	{ 
		p_healthbar->resizeWidth((int)((float)getHealth() * p_healthbarBackplate->getWidth() 
			                     / (float)getHealthMax()));
		p_healthbar->setPos({ getPos().x + int(0.25 * TILE_WIDTH),
			                getPos().y + int(0.9 * TILE_WIDTH) });
		p_healthbarBackplate->setPos({ getPos().x + int(0.25 * TILE_WIDTH), 
			                         getPos().y + int(0.9 * TILE_WIDTH) });
	}


protected:

	SpellBook* p_spellBook;

	UIIcon* p_healthbar = nullptr;
	UIIcon* p_healthbarBackplate = nullptr;


	int m_movementCost;
	int m_energy;
	int m_energyMax;
	int m_health;
	int m_healthMax;
	bool m_isFriendly;
	std::string m_name;
};