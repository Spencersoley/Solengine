#include "Model.h"

#include <Solengine/ErrorHandler.h>

Model::Model() 
{
}

Model::~Model()
{
}

void Model::init(float physicsSpeed)
{
	m_physicsSpeed = physicsSpeed;
}

void Model::update(int pauseDuration, std::vector<Unit*> units, Unit* currentUnit)
{
	float adjustedDeltaTicks = (getDeltaTicks() - pauseDuration) * m_physicsSpeed;
	
	//check current unit's energy.
	//set wakable tiles as current unit tile + energy/5 
    // steps = energy/5 
	// all tiles, isWalkable = false
	// current tile [a][b]
	// colour tiles i from [a][b]
	//     
	// if ![a+i][b].isObstacle ![a+i][b].isOccupied, [a][b].isWalkable = true
	
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

