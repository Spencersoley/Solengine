#include "Model.h"

#include <Solengine/ErrorHandler.h>

Model::Model() : m_globalFrameCount(0)
{
}

Model::~Model()
{
}

void Model::init(float gameSpeed)
{
	m_gameSpeed = gameSpeed;
}

void Model::update(int pauseDuration)
{
	m_globalFrameCount++;
	float adjustedDeltaTicks = (getDeltaTicks() - pauseDuration) * m_gameSpeed;
	updateAgents(adjustedDeltaTicks);
}

Uint32 Model::getDeltaTicks()
{
	static Uint32 prevTicks = SDL_GetTicks();
	Uint32 deltaTicks = SDL_GetTicks() - prevTicks;
	prevTicks = SDL_GetTicks();
	return deltaTicks;
}

void Model::updateAgents(float adjustedDeltaTicks)
{
}
