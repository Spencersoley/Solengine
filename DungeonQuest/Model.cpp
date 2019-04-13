#include "Model.h"

#include <Solengine/ErrorHandler.h>

Model::Model() 
{
}

Model::~Model()
{
}

void Model::init(float physicsSpeed, Solengine::Camera2D* cam)
{
	m_physicsSpeed = physicsSpeed;
	p_SOL_cam = cam;
}

Solengine::GameState Model::update(int pauseDuration, std::vector<Unit*> units)
{
	float adjustedDeltaTicks = (getDeltaTicks() - pauseDuration) * m_physicsSpeed;

	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;
	const int SCROLL_SPEED = 5;

	 Solengine::GameState state = m_SOL_inputManager.processInput();

	if (m_SOL_inputManager.keyPress(SDLK_p))          state = Solengine::GameState::PAUSE;
	if (m_SOL_inputManager.keyPress(SDLK_r))          state = Solengine::GameState::TURNOVER;
	if (m_SOL_inputManager.keyState(SDLK_w))          p_SOL_cam->shiftPosition(glm::vec2{ 0, SCROLL_SPEED });
	if (m_SOL_inputManager.keyState(SDLK_s))          p_SOL_cam->shiftPosition(glm::vec2{ 0, -SCROLL_SPEED });
	if (m_SOL_inputManager.keyState(SDLK_a))          p_SOL_cam->shiftPosition(glm::vec2{ -SCROLL_SPEED, 0 });
	if (m_SOL_inputManager.keyState(SDLK_d))          p_SOL_cam->shiftPosition(glm::vec2{ SCROLL_SPEED, 0 });


	if (getLeftMouse())                               setSelectedUnit(selectionCheck(units));

	//setWalkableTiles(p_tileMap, p_currentUnit);

	highlightTile(p_tileMap->p_tiles);


	if (state == Solengine::GameState::TURNOVER)
         state = nextTurn(units);


	attemptMovement(getMouseCoordinates());

	updateStatsDisplay(p_currentUnit, p_currentUnitIcon, p_currentUnitNameTextBox, p_currentUnitHealthText, p_currentUnitEnergyText);
	updateStatsDisplay(p_selectedUnit, p_selectedUnitIcon, p_selectedUnitNameTextBox, p_selectedUnitHealthText, p_selectedUnitEnergyText);

	if (p_currentUnit != nullptr && p_currentUnitBox != nullptr)
	{
		p_currentUnitBox->setPos(p_currentUnit->getPos());
		p_currentUnitBox->setColour({ 0, 0, 255, 255 });
	}

	if (p_selectedUnit != nullptr && p_selectionBox != nullptr)
	{
		p_selectionBox->setPos(p_selectedUnit->getPos());

		if (p_selectedUnit->getIsFriendly())
			p_selectionBox->setColour({ 0, 255, 0, 255 });
		else
			p_selectionBox->setColour({ 255, 0, 0, 255 });
	}
 
	setWalkableTiles(p_tileMap, p_currentUnit);


	if (state == Solengine::GameState::TURNOVER)
		state == Solengine::GameState::PLAY;

	return state;
}

Uint32 Model::getDeltaTicks()
{
	static Uint32 prevTicks = SDL_GetTicks();
	Uint32 deltaTicks = SDL_GetTicks() - prevTicks;
	prevTicks = SDL_GetTicks();
	return deltaTicks;
}

void Model::attemptMovement(glm::vec2 coords)
{
	if (getLeftMouse())
	{
		if (p_tileMap->p_tiles[coords.y][coords.x]->m_isWalkable && !p_tileMap->p_tiles[coords.y][coords.x]->m_isOccupied)
		{
			int steps;
			//get tile distance in steps (rough, not the right way to do this)
			steps = (abs(coords.y - p_currentUnit->getCoords().y) + abs(coords.x - p_currentUnit->getCoords().x));
			p_currentUnit->setPos({ coords.x*TILE_WIDTH, coords.y*TILE_WIDTH } );
			p_currentUnit->removeEnergy(steps * 5);
		}
	}
}


void Model::setSelectedUnit(Unit* selectedUnit)
{
	if (p_selectedUnit != selectedUnit)
	{
		p_selectedUnit = selectedUnit;
		updateStatsDisplay(selectedUnit, p_selectedUnitIcon, p_selectedUnitNameTextBox, p_selectedUnitHealthText, p_selectedUnitEnergyText);
	}
}

Unit* Model::selectionCheck(std::vector<Unit*> units)
{
	glm::vec2 clickWorldPos = getMouseWorldPosition();

	for (size_t i = 0; i < units.size(); i++)
	{
		glm::vec2 unitPos = units[i]->getPos();

		if (clickWorldPos.x >= unitPos.x && clickWorldPos.x <= unitPos.x + TILE_WIDTH
			&& clickWorldPos.y >= unitPos.y && clickWorldPos.y <= unitPos.y + TILE_WIDTH)
			     return units[i];
	}
	return nullptr;
}

void Model::updateStatsDisplay(Unit* unit, UIIcon* icon, UIText* name, UIText* health, UIText* energy)
{
	//set icon
	if (icon != nullptr) //selected
	{
		if (unit != nullptr)
			icon->setTexture(unit->getTextureID());
		else
			icon->setTexture(-1);
	}

	//set name
	if (name != nullptr) //selected
	{
		if (unit != nullptr)
			name->updateText(unit->getName());
		else 
			name->updateText("");
	}

	//set health
	if (health != nullptr)
	{
		if (unit != nullptr)
			health->updateText(std::to_string(unit->getHealth()) + "/" + std::to_string(unit->getHealthMax()));
		else
			health->updateText("");
	}

	//set energy
	if (energy != nullptr)
	{
		if (unit != nullptr)
			energy->updateText(std::to_string(unit->getEnergy()) + "/" + std::to_string(unit->getEnergyMax()));
		else
			energy->updateText("");
	}
}

void Model::highlightTile(std::vector<std::vector<Tile*>> tiles)
{
	static glm::ivec2 previousMouseCoords;
	glm::ivec2 mouseCoords = getMouseCoordinates();

	//check for change in mouseCoords
	if (mouseCoords != previousMouseCoords)
	{
		//if mousecoords reposition hover tile
		if (checkIfCoordsInBound(tiles, mouseCoords))
		{
			if (!tiles[mouseCoords.y][mouseCoords.x]->m_isObstacle)
			{
				p_hoverHighlight->setVisible(true);
				p_hoverHighlight->setPos(mouseCoords * TILE_WIDTH);
			}
			else
			{
				p_hoverHighlight->setVisible(false);
			}
		}
		else
		{
			p_hoverHighlight->setVisible(false);
		}
	}
 
	previousMouseCoords = mouseCoords;
}

bool Model::checkIfCoordsInBound(std::vector<std::vector<Tile*>> tiles, glm::ivec2 coords)
{
	if ((size_t)coords.x > tiles[0].size()) return false;
	if (coords.x < 0) return false;
	if ((size_t)coords.y > tiles.size()) return false;
	if (coords.y < 0) return false;

	return true;
}

void Model::setWalkableTiles(TileMap* tileMap, Unit* currentUnit)
{
	tileMap->resetWalkable();
	std::vector<glm::vec2> walkableTiles = tileMap->getWalkablePos(currentUnit->getCoords(), floor(currentUnit->getEnergy() / 5));
	p_walkableHighlight->setMultidraw(walkableTiles);	
}

Solengine::GameState Model::nextTurn(std::vector<Unit*> units)
{
	p_currentUnit = units[++m_turnCounter%units.size()];
	if (p_currentUnit == p_selectedUnit) 
		p_selectedUnit = nullptr;
	//p_currentUnit->newTurn();
	return Solengine::GameState::PLAY;
}