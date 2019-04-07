#include "Unit.h"

#include "Solengine/ResourceManager.h"

Unit::Unit()
{
}

Unit::~Unit()
{
}

void Unit::draw()
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	static Solengine::ColourRGBA8 colour = { 255, 255, 255, 255 };

	glm::vec4 destRect;
	destRect.x = m_position.x;
	destRect.y = m_position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;

	p_SOL_SB->draw(destRect, uvRect, m_textureID, 0.0f, colour);
}
