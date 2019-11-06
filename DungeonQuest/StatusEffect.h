#pragma once

#include <iostream>
#include <Solengine/Vertex.h>

enum class StatusType { DEBUFF, BUFF };

class StatusEffect
{
public:
	StatusEffect();
	virtual ~StatusEffect();

	std::string GetName() const { return m_name; }
	int GetDamage() const { return m_damage; }	
	int GetDuration() const { return m_duration; }
	int GetTextureID() const { return m_textureID; }
	Solengine::ColourRGBA8 GetColour() const { return m_colour; }

	int Tick() { return m_damage; }

	StatusType m_statusType;

protected:
	std::string m_name;

	int m_damage;
	int m_duration;

	Solengine::ColourRGBA8 m_colour;
	unsigned int m_textureID;
};

