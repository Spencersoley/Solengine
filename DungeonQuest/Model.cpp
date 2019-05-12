#include "Solengine/ErrorHandler.h"

#include "Model.h"

Model::Model() 
{
}

Model::~Model()
{
}

void Model::init(float physicsSpeed, Solengine::Camera2D* cam, int sw, int sh)
{
	m_physicsSpeed = physicsSpeed;
	p_SOL_cam = cam;
	m_screenHeight = sh;
	m_screenWidth = sw;
}

void Model::awake(std::vector<Unit*> units)
{
	for (size_t i = 0; i < units.size(); i++)
		units[i]->newTurn();

	for (size_t i = 0; i < units.size(); i++)
		if (units[i]->getSpeed() < p_currentUnit->getSpeed()) p_currentUnit = units[i];

	updateTileStates(p_tileMap, p_currentUnit);
	updateCurrentUnitBox(p_currentUnit, p_currentUnitBox);
	updateSelectedUnitBox(p_selectedUnit, p_selectionBox);
	updateStatsDisplay(p_currentUnit, p_currentUnitIcon, 
		               p_currentUnitNameText, p_currentUnitHealthText, 
		               p_currentUnitEnergyText, p_currentUnitSpeedText);
	updateStatsDisplay(p_selectedUnit, p_selectedUnitIcon, 
		               p_selectedUnitNameText, p_selectedUnitHealthText,
		               p_selectedUnitEnergyText, p_selectedUnitSpeedText);
	updateSpellDisplay(p_currentUnit);

	updateSelectedSpellBox();

	for (size_t i = 0; i < p_spellText.size(); i++) 
		p_mouseoverable.push_back(p_spellText[i]);

	for (size_t i = 0; i < units.size(); i++) 
		units[i]->updateHealthbar();

}

Solengine::GameState Model::update(int pauseDur, std::vector<Unit*> units)
{
	const float physSpeed = m_physicsSpeed;
	float adjustedDeltaTicks = (getDeltaTicks() - pauseDur) * physSpeed;

	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;
	float SCROLL_SPEED = 20 * adjustedDeltaTicks;

	entityNeedsDeletion(0);

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

	if (m_SOL_inputManager.keyPress(SDLK_c))
		m_combatLog.scrollCombatLog(true);

	if (m_SOL_inputManager.keyPress(SDLK_v))
		m_combatLog.scrollCombatLog(false);

	if (m_SOL_inputManager.keyPress(SDLK_f))
	{
		changeSpell();
		updateHighlight(p_tileMap->p_tiles, mouseCoords, p_hoverHighlight);
	}


	//////////////     Mouse Control       /////////////////
	glm::vec2 msp = getMouseScreenPos();

	if (msp.y > 130) //exclude backplate
	{
		if (m_SOL_inputManager.keyPress(SDL_BUTTON_LEFT))
		{
			if (!movement(mouseCoords, p_tileMap, p_currentUnit))
			    setSelectedUnit(selectionCheck(units, mouseCoords));
		}
			
		if (m_SOL_inputManager.keyPress(SDL_BUTTON_RIGHT))
		{
			if (!movement(mouseCoords, p_tileMap, p_currentUnit))
			    attack(mouseCoords, p_tileMap, p_currentUnit, units);
		}		

		if (mouseCoords != previousMouseCoords)
			updateHighlight(p_tileMap->p_tiles, mouseCoords, p_hoverHighlight);
	}
	else 
	{
		updateHighlight(p_tileMap->p_tiles, { 0, 0 }, p_hoverHighlight);


		//Doesn't work as intended. Perhaps we should create dedicated button images?
		/*
		for (size_t i = 0; i < p_mouseoverable.size(); i++)
		{
			if (p_mouseoverable[i]->checkMouseover(msp))
				if (m_SOL_inputManager.keyPress(SDL_BUTTON_LEFT))
				{
					if (p_mouseoverable[i] == p_spellText[i])
					{
						m_currentSpellIndex = i;
						if (p_currentUnit->m_moveSet.p_spells[m_currentSpellIndex]->getCost() == 0)
							changeSpell();   
						updateSelectedSpellBox();
					}			
				}

		}
		*/
	}
	
	if (state == Solengine::GameState::TURNOVER)                                   
		state = nextTurn(units, p_currentUnit, p_selectedUnit);
	
	for (size_t i = 0; i < p_visualEffects.size(); i++)
		if (!p_visualEffects[i]->updateEffect(adjustedDeltaTicks))
		{
			p_visualEffects[i] = p_visualEffects.back();
			p_visualEffects.pop_back();
			i--;
		}
		

	previousMouseCoords = mouseCoords;
	return state;
}

Uint32 Model::getDeltaTicks()
{
	static Uint32 prevTicks = SDL_GetTicks();
	Uint32 deltaTicks = SDL_GetTicks() - prevTicks;
	prevTicks = SDL_GetTicks();
	return deltaTicks;
}

bool Model::movement(glm::ivec2 coords, TileMap* tileMap, Unit* currentUnit)
{
	Tile* tarTile = tileMap->getTileByCoords(coords);
	Tile* currentTile = tileMap->getTileByCoords(currentUnit->getCoords());
	
	if (tarTile == nullptr) return false;
	
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
			               p_currentUnitEnergyText, p_currentUnitSpeedText);
		
		currentUnit->redraw();

		currentUnit->updateHealthbar();

		return true;
	}
	
	return false;
}

bool Model::attack(glm::ivec2 mouseCoords, TileMap* tileMap, Unit* currentUnit, 
	               std::vector<Unit*> units)
{
	Unit* tarUnit = selectionCheck(units, mouseCoords);
    
	if (tarUnit != nullptr)
	{
		if (currentUnit->m_moveSet.p_spells[m_currentSpellIndex]->getCost()
			<= currentUnit->getEnergy())
		{
		    if (checkIfTileReachable(currentUnit->getCoords(), tarUnit->getCoords(),
			currentUnit->m_moveSet.p_spells[m_currentSpellIndex]->getRange()))
		    { 
				if (currentUnit != tarUnit)
				{
					Spell* castSpell = currentUnit->m_moveSet.p_spells[m_currentSpellIndex];
					castSpell->cast(currentUnit, tarUnit);
					updateTileStates(tileMap, currentUnit);

					updateStatsDisplay(currentUnit, p_currentUnitIcon,
						p_currentUnitNameText, p_currentUnitHealthText,
						p_currentUnitEnergyText, p_currentUnitSpeedText);
					updateStatsDisplay(tarUnit, p_selectedUnitIcon,
						p_selectedUnitNameText, p_selectedUnitHealthText,
						p_selectedUnitEnergyText, p_selectedUnitSpeedText);
					setSelectedUnit(tarUnit);

					tarUnit->updateHealthbar();

					std::string dmgstr = std::to_string(
						castSpell->getDamage());

					m_combatLog.announce("EVENT: " + currentUnit->getName() +
						" hit " + tarUnit->getName() +
						" with " + castSpell->getName() + 
						" for " + dmgstr + " damage");


					/////////////////////////////
	                p_visualEffects.push_back(new UIText({ 0, 0 }, 1.0f,
						new Solengine::Font("Fonts/Px437_VGA_SquarePx.ttf", 48),
						 "", { 255, 0, 0, 255 }));

					p_visualEffects.back()->activate("-" + dmgstr, { tarUnit->getPos().x + 0.6f*TILE_WIDTH,
						 	tarUnit->getPos().y + 0.6f*TILE_WIDTH });

					p_visualEffects.push_back(new UIIcon({ 0, 0 }, 48, 48,
						castSpell->getTextureID(),
						castSpell->getColour()));

					p_visualEffects.back()->activate( { tarUnit->getPos().x + 0.1f*TILE_WIDTH, tarUnit->getPos().y } );
					 ////////////////////////

					if (tarUnit->getHealth() < 1)
					{
						entityNeedsDeletion(1);
						tarUnit->death();
						m_combatLog.announce("EVENT! " + tarUnit->getName() + " has died!");
						setSelectedUnit(nullptr);
						tileMap->getTileByCoords(tarUnit->getCoords())->m_isOccupied = false;
					}

					return true;
				}
				else m_combatLog.announce("WARNING! " + currentUnit->getName()
					+ " can't attack itself!");		
		    }
	    	else m_combatLog.announce("WARNING! " + tarUnit->getName() + 
                  " is out of range of " + 
	     		  currentUnit->getName() + "'s " + 
                  currentUnit->m_moveSet.p_spells[m_currentSpellIndex]
                  ->getName() );
		}
		else m_combatLog.announce("WARNING! " + currentUnit->getName() +
			" has no NRG for " + currentUnit->
			m_moveSet.p_spells[m_currentSpellIndex]->getName());
	}

	return false;
}

void Model::setSelectedUnit(Unit* selectedUnit)
{
	if (p_selectedUnit != selectedUnit && p_currentUnit != selectedUnit)
	{
		p_selectedUnit = selectedUnit;
		updateStatsDisplay(selectedUnit, p_selectedUnitIcon, 
			               p_selectedUnitNameText, p_selectedUnitHealthText, 
			               p_selectedUnitEnergyText, p_selectedUnitSpeedText);

		updateSelectedUnitBox(selectedUnit, p_selectionBox);
	}
}

Unit* Model::selectionCheck(std::vector<Unit*> units, glm::ivec2 coords)
{
	for (size_t i = 0; i < units.size(); i++)
		if (units[i]->getCoords() == coords) return units[i];
	
	return nullptr;
}

void Model::changeSpell()
{
	m_currentSpellIndex++;
	m_currentSpellIndex = m_currentSpellIndex % 4;
	if (p_currentUnit->m_moveSet.p_spells[m_currentSpellIndex]->getCost() == 0)
		changeSpell();

	updateSelectedSpellBox();
}

void Model::updateStatsDisplay(Unit* unit, UIIcon* icon, UIText* name, 
	                           UIText* health, UIText* energy, UIText* speed)
{
	//set icon
	if (icon != nullptr) 
	{
		if (unit != nullptr) icon->setTexture(unit->getTextureID());
		else icon->setTexture(-1);

		icon->redraw();
	}

	//set name
	if (name != nullptr)
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

	if (speed != nullptr)
	{
		if (unit != nullptr)
			speed->updateText(std::to_string(unit->getSpeed()));
		else speed->updateText("");

		speed->redraw();
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
			updateHighlightColour(mouseCoords, hoverHighlight);
			hoverHighlight->setVisible(true);
			hoverHighlight->setPos(mouseCoords * TILE_WIDTH);
			hoverHighlight->redraw();
		}
		else hoverHighlight->setVisible(false);
	}
    else hoverHighlight->setVisible(false);
}

void Model::updateHighlightColour(glm::ivec2 mouseCoords, UIIcon* hoverHighlight)
{
	if (checkIfTileReachable(mouseCoords, p_currentUnit->getCoords(),
		p_currentUnit->m_moveSet.p_spells[m_currentSpellIndex]->getRange()))
		hoverHighlight->setColour({ 255, 15, 15, 200 });
	else hoverHighlight->setColour({ 100, 100, 100, 200 });
}

bool Model::checkIfTileReachable(glm::ivec2 mouseCoords, glm::ivec2 unitCoords, int spellRange)
{
	int tileDist = (mouseCoords.x - unitCoords.x) * (mouseCoords.x - unitCoords.x)
		+ (mouseCoords.y - unitCoords.y) * (mouseCoords.y - unitCoords.y);

	if (spellRange < sqrt((float)tileDist)) return false;

    return true;
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
                       (int)floor(currentUnit->getEnergy() 
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
		currentUnitBox->setColour({ 0, 255, 0, 255 });
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
			selectBox->setColour({ 200, 200, 200, 255 });
		else selectBox->setColour({ 255, 0, 0, 255 });
	}
	else selectBox->setVisible(false);

	selectBox->redraw();
}

Solengine::GameState Model::nextTurn(std::vector<Unit*> units,
	Unit* currentUnit, Unit* selectedUnit)
{
	currentUnit->resetEnergy();

	currentUnit->newTurn();

	for (size_t i = 0; i < units.size(); i++)
		if (units[i]->getTurnPoints() < currentUnit->getTurnPoints()) currentUnit = units[i];

	setCurrentUnit(currentUnit);
	p_SOL_cam->setPosition(currentUnit->getPos() - glm::vec2(0.5f * TILE_WIDTH, 0.5f * TILE_WIDTH));

	if (currentUnit == selectedUnit) setSelectedUnit(nullptr);

	updateTileStates(p_tileMap, currentUnit);

	updateCurrentUnitBox(currentUnit, p_currentUnitBox);
	updateStatsDisplay(currentUnit, p_currentUnitIcon, p_currentUnitNameText,
		p_currentUnitHealthText, p_currentUnitEnergyText, p_currentUnitSpeedText);
	m_currentSpellIndex = 0;
	updateSpellDisplay(currentUnit);
	updateSelectedSpellBox();

	return Solengine::GameState::PLAY;
}

std::vector<Drawable*> Model::getEffects()
{

	return p_visualEffects;
}