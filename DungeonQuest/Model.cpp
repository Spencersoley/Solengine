#include "Solengine/ErrorHandler.h"

#include "Model.h"

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

void Model::awake()
{
	updateTileStates(p_tileMap, p_currentUnit);
	updateCurrentUnitBox(p_currentUnit, p_currentUnitBox);
	updateSelectedUnitBox(p_selectedUnit, p_selectionBox);
	updateStatsDisplay(p_currentUnit, p_currentUnitIcon, 
		               p_currentUnitNameText, p_currentUnitHealthText, 
		               p_currentUnitEnergyText);
	updateStatsDisplay(p_selectedUnit, p_selectedUnitIcon, 
		               p_selectedUnitNameText, p_selectedUnitHealthText,
		               p_selectedUnitEnergyText);
	updateSpellDisplay(p_currentUnit);

	updateSelectedSpellBox();
}

Solengine::GameState Model::update(int pauseDur, std::vector<Unit*> units)
{
	float adjustedDeltaTicks = (getDeltaTicks() - pauseDur) * m_physicsSpeed;

	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;
	const int SCROLL_SPEED = 5;

	Solengine::GameState state = m_SOL_inputManager.processInput();

	static glm::ivec2 previousMouseCoords;
	glm::ivec2 mouseCoords = getMouseCoordinates();

	if (m_SOL_inputManager.keyPress(SDLK_p))
	    state = Solengine::GameState::PAUSE;

	if (m_SOL_inputManager.keyPress(SDLK_r))
	    state = Solengine::GameState::TURNOVER;

	if (m_SOL_inputManager.keyState(SDLK_w))
		p_SOL_cam->shiftPosition(glm::vec2{ 0, SCROLL_SPEED });

	if (m_SOL_inputManager.keyState(SDLK_s))
		p_SOL_cam->shiftPosition(glm::vec2{ 0, -SCROLL_SPEED });
	
	if (m_SOL_inputManager.keyState(SDLK_a))
		p_SOL_cam->shiftPosition(glm::vec2{ -SCROLL_SPEED, 0 });

	if (m_SOL_inputManager.keyState(SDLK_d))
		p_SOL_cam->shiftPosition(glm::vec2{ SCROLL_SPEED, 0 });

	if (m_SOL_inputManager.keyPress(SDLK_f))
		changeSpell();

	if (getMouseScreenPos().y < 470) //exclude backplate
	{
		if (getLeftMouse())
			setSelectedUnit(selectionCheck(units, mouseCoords));

		if (getRightMouse())
			movement(getMouseCoordinates(), p_tileMap, p_currentUnit);
	}

	if (mouseCoords != previousMouseCoords)
		updateHighlight(p_tileMap->p_tiles, mouseCoords, p_hoverHighlight);


	if (state == Solengine::GameState::TURNOVER)                                   
		state = nextTurn(units, p_currentUnit, p_selectedUnit);
	
	previousMouseCoords = mouseCoords;

	//470

	return state;
}

Uint32 Model::getDeltaTicks()
{
	static Uint32 prevTicks = SDL_GetTicks();
	Uint32 deltaTicks = SDL_GetTicks() - prevTicks;
	prevTicks = SDL_GetTicks();
	return deltaTicks;
}

void Model::movement(glm::ivec2 coords, TileMap* tileMap, Unit* currentUnit)
{
	Tile* tarTile = tileMap->getTileByCoords(coords);
	Tile* currentTile = tileMap->getTileByCoords(currentUnit->getCoords());
	if (tarTile->m_isWalkable && !tarTile->m_isOccupied)
	{
        currentUnit->setPos({ coords.x * TILE_WIDTH, coords.y * TILE_WIDTH } );
        currentUnit->removeEnergy(tarTile->getDist() 
			                      * currentUnit->getMoveCost());         

		currentTile->setOccupied(false);
		tarTile->setOccupied(true);

		updateTileStates(tileMap, currentUnit);

		updateCurrentUnitBox(currentUnit, p_currentUnitBox);
        updateStatsDisplay(currentUnit, p_currentUnitIcon, 
                           p_currentUnitNameText, p_currentUnitHealthText,
			               p_currentUnitEnergyText);
		
		currentUnit->redraw();
	}
}

void Model::setSelectedUnit(Unit* selectedUnit)
{
	if (p_selectedUnit != selectedUnit && p_currentUnit != selectedUnit)
	{
		p_selectedUnit = selectedUnit;
		updateStatsDisplay(selectedUnit, p_selectedUnitIcon, 
			               p_selectedUnitNameText, p_selectedUnitHealthText, 
			               p_selectedUnitEnergyText);

		updateSelectedUnitBox(selectedUnit, p_selectionBox);
	}
}

Unit* Model::selectionCheck(std::vector<Unit*> units, glm::ivec2 coords)
{
	for (size_t i = 0; i < units.size(); i++)
		if (units[i]->getCoords() == coords) return units[i];
	
	return nullptr;
}

void Model::changeSpell(int spell)
{
	if (p_currentUnit->m_moveSet.p_spells[spell]->getCost() != 0)
		m_currentSpellIndex = spell;

	updateSelectedSpellBox();
}

void Model::changeSpell()
{
	m_currentSpellIndex++;
	m_currentSpellIndex = m_currentSpellIndex % 4;
	if (p_currentUnit->m_moveSet.p_spells[m_currentSpellIndex]->getCost() == 0)
		changeSpell();

	updateSelectedSpellBox();
}

/*
void Model::updateSpellDisplay()
{
	for (size_t i = 0; i < p_spellStats.size(); i++)
	{
		if (p_spellText == nullptr) continue;
	
		p_spellStats[i]->updateText(p_spell);
	}
}
*/

void Model::updateStatsDisplay(Unit* unit, UIIcon* icon, UIText* name, 
	                           UIText* health, UIText* energy)
{
	//set icon
	if (icon != nullptr) //selected
	{
		if (unit != nullptr) icon->setTexture(unit->getTextureID());
		else icon->setTexture(-1);

		icon->redraw();
	}

	//set name
	if (name != nullptr) //selected
	{
		if (unit != nullptr) name->updateText(unit->getName());
		else name->updateText("");

		name->redraw();
	}

	//set health
	if (health != nullptr)
	{
		if (unit != nullptr) 
			health->updateText(std::to_string(unit->getHealth())
                               + "/" + std::to_string(unit->getHealthMax()));
		else health->updateText("");

		health->redraw();
	}

	//set energy
	if (energy != nullptr)
	{
        if (unit != nullptr) 
			energy->updateText(std::to_string(unit->getEnergy()) 
			                   + "/" + std::to_string(unit->getEnergyMax()));
		else energy->updateText("");

		energy->redraw();
	}
}

void Model::updateSelectedSpellBox()
{
	p_selectedSpellBox->setPos(p_spellText[m_currentSpellIndex]->getPos());
	p_selectedSpellBox->redraw();
}

void Model::updateSpellDisplay(Unit* currentUnit)
{
	for (size_t i = 0; i < p_spellText.size(); i++)
	{
		if (i < currentUnit->m_moveSet.moveSetSize())
		{
			p_spellText[i]->updateText(currentUnit->m_moveSet.getSpell(i)->getName());
			p_spellText[i]->setVisible(true);
		}
		else
		{
			p_spellText[i]->updateText(" ");
			p_spellText[i]->setVisible(false);
		}
        
		p_spellText[i]->redraw();
	}
}

void Model::updateHighlight(std::vector<std::vector<Tile*>> tiles,
	                      glm::ivec2 mouseCoords, UIIcon* hoverHighlight)
{
	if (checkIfCoordsInBound(tiles, mouseCoords))
	{
		if (!tiles[mouseCoords.y][mouseCoords.x]->m_isObstacle)
		{
			hoverHighlight->setVisible(true);
			hoverHighlight->setPos(mouseCoords * TILE_WIDTH);
			hoverHighlight->redraw();
		}
		else hoverHighlight->setVisible(false);
	}
    else hoverHighlight->setVisible(false);
}

bool Model::checkIfCoordsInBound(std::vector<std::vector<Tile*>> tiles, 
	                             glm::ivec2 coords)
{
	if ((size_t)coords.x >= tiles[0].size()) return false;
	if (coords.x < 0)                        return false;
	if ((size_t)coords.y >= tiles.size())    return false;
	if (coords.y < 0)                        return false;

	return true;
}

void Model::updateTileStates(TileMap* tileMap, Unit* currentUnit)
{
	tileMap->resetWalkable();
	std::vector<glm::vec2> walkableTiles = tileMap->
		getWalkablePos(currentUnit->getCoords(), 
                       floor(currentUnit->getEnergy() 
						     / currentUnit->getMoveCost()));
	p_walkableHighlight->setMultidraw(walkableTiles);	
	p_walkableHighlight->redraw();
}

void Model::updateCurrentUnitBox(Unit* currentUnit, UIIcon* currentUnitBox)
{
	if (currentUnit != nullptr)
	{
		currentUnitBox->setVisible(true);
		currentUnitBox->setPos(currentUnit->getPos());
		currentUnitBox->setColour({ 0, 0, 255, 255 });
	}
	else currentUnitBox->setVisible(false);

	currentUnitBox->redraw();
}

void Model::updateSelectedUnitBox(Unit* selectedUnit, UIIcon* selectBox)
{
	if (selectedUnit != nullptr)
	{
		selectBox->setVisible(true);
		selectBox->setPos(selectedUnit->getPos());

        if (selectedUnit->getIsFriendly()) 
			selectBox->setColour({ 0, 255, 0, 255 });
		else selectBox->setColour({ 255, 0, 0, 255 });
	}
	else selectBox->setVisible(false);

	selectBox->redraw();
}

Solengine::GameState Model::nextTurn(std::vector<Unit*> units,
	Unit* currentUnit, Unit* selectedUnit)
{
	currentUnit->resetEnergy();
	currentUnit = units[++m_turnCounter%units.size()];
	setCurrentUnit(currentUnit);
	if (currentUnit == selectedUnit) setSelectedUnit(nullptr);

	updateTileStates(p_tileMap, currentUnit);

	updateCurrentUnitBox(currentUnit, p_currentUnitBox);
	updateStatsDisplay(currentUnit, p_currentUnitIcon, p_currentUnitNameText,
		p_currentUnitHealthText, p_currentUnitEnergyText);
	updateSpellDisplay(currentUnit);
	changeSpell(0);

	return Solengine::GameState::PLAY;
}