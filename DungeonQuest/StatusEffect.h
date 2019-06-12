#pragma once

#include <iostream>
#include <Solengine/Vertex.h>

enum class StatusType { DEBUFF, BUFF };

class StatusEffect
{
public:
	StatusEffect();
	virtual ~StatusEffect();

	StatusType m_statusType;
	std::string getName() const { return m_name; }
	int getDamage() const { return m_damage; }	
	int getDuration() const { return m_duration; }
	int getTextureID() const { return m_textureID; }
	Solengine::ColourRGBA8 getColour() const { return m_colour; }

	int tick() { return m_damage; }

protected:
	std::string m_name;

	int m_damage;
	int m_duration;

	Solengine::ColourRGBA8 m_colour;
	unsigned int m_textureID;
};

