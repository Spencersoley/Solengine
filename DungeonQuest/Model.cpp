//#include "Solengine/ErrorHandler.h"

#include "Model.h"

Model::Model() {}

Model::~Model() {}

void Model::Init(float physicsSpeed, Solengine::ICamera* cam, int sw, int sh)
{
	m_physicsSpeed = physicsSpeed;
	p_SOL_cam = cam;
	m_screenHeight = sh;
	m_screenWidth = sw;
}

void Model::Awake(std::vector<Unit*> units)
{
	turnCounter = 0;
	SetCurrentUnit(units[turnCounter]);

	for (size_t i = 0; i < units.size(); i++)
		units[i]->NewTurn();

	updateTileStates(p_tileMap, p_currentUnit);
	updateCurrentUnitBox(p_currentUnit, p_currentUnitBox);
	updateSelectedUnitBox(p_selectedUnit, p_selectionBox);
	updateStatsDisplay(p_currentUnit, p_currentUnitIcon, p_currentUnitNameText, 
	    p_currentUnitHealthText, p_currentUnitEnergyText, p_currentUnitSpeedText,
		p_currentUnitCombatPointsText);
	updateStatsDisplay(p_selectedUnit, p_selectedUnitIcon, p_selectedUnitNameText, 
        p_selectedUnitHealthText, p_selectedUnitEnergyText, p_selectedUnitSpeedText,
		p_selectedUnitCombatPointsText);
	updateSpellDisplay(p_currentUnit);

	updateSelectedSpellBox();

	for (size_t i = 0; i < p_spellText.size(); i++) 
		p_mouseoverable.push_back(p_spellText[i]);

	for (size_t i = 0; i < units.size(); i++) 
		units[i]->UpdateHealthbar();
}

Solengine::GameState Model::Update(int pauseDur, std::vector<Unit*> units)
{
	static float physSpeed = m_physicsSpeed;
	float adjustedDeltaTicks = (getDeltaTicks() - pauseDur) * physSpeed;

	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;
	float SCROLL_SPEED = 20 * adjustedDeltaTicks;

	Solengine::GameState state = m_SOL_inputManager.ProcessInput();

	static glm::ivec2 previousMouseCoords;
	glm::ivec2 mouseCoords = GetMouseCoordinates();

	if (m_SOL_inputManager.KeyPress(SDLK_p))
	    state = Solengine::GameState::PAUSE;

	if (m_SOL_inputManager.KeyPress(SDLK_r))
	    state = Solengine::GameState::TURNOVER;

	if (m_SOL_inputManager.KeyState(SDLK_w))
		p_SOL_cam->ShiftPosition(glm::vec2{ 0, SCROLL_SPEED });

	if (m_SOL_inputManager.KeyState(SDLK_s))
		p_SOL_cam->ShiftPosition(glm::vec2{ 0, -SCROLL_SPEED });
	
	if (m_SOL_inputManager.KeyState(SDLK_a))
		p_SOL_cam->ShiftPosition(glm::vec2{ -SCROLL_SPEED, 0 });

	if (m_SOL_inputManager.KeyState(SDLK_d))
		p_SOL_cam->ShiftPosition(glm::vec2{ SCROLL_SPEED, 0 });

	if (m_SOL_inputManager.KeyPress(SDLK_c))
		m_combatLog.scrollCombatLog(true);

	if (m_SOL_inputManager.KeyPress(SDLK_v))
		m_combatLog.scrollCombatLog(false);

	if (m_SOL_inputManager.KeyPress(SDLK_f))
		changeSpell(0, mouseCoords);

	float mwp = GetMouseWheel();

	if (mwp != 0) changeSpell(mwp, mouseCoords);

	//////////////     Mouse Control       /////////////////
	glm::vec2 msp = GetMouseScreenPos();

	static int overlayCutoff = m_UIpanelHeight;

	if (msp.y > overlayCutoff) //exclude backplate
	{
		if (m_SOL_inputManager.KeyPress(SDL_BUTTON_LEFT))
		{
			if (!movement(mouseCoords, p_tileMap, p_currentUnit))
			    SetSelectedUnit(selectionCheck(units, mouseCoords));
		}
			
		if (m_SOL_inputManager.KeyPress(SDL_BUTTON_RIGHT))
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
	}
	
	if (state == Solengine::GameState::TURNOVER) state = endTurn(units, p_currentUnit);
	
	m_visualEffectManager.UpdateEffects(adjustedDeltaTicks);
		
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
	Tile* tarTile = tileMap->GetTileByCoords(coords);
	Tile* currentTile = tileMap->GetTileByCoords(currentUnit->GetCoords());
	
	if (tarTile == nullptr) return false;
	
	if (tarTile->m_isWalkable && !tarTile->m_isOccupied)
	{
        currentUnit->SetPos({ coords.x * TILE_WIDTH, coords.y * TILE_WIDTH } );
        currentUnit->RemoveEnergy(tarTile->GetDist() 
			                      * currentUnit->GetMoveCost());         

		currentTile->SetOccupied(false);
		tarTile->SetOccupied(true);

		updateTileStates(tileMap, currentUnit);

		updateCurrentUnitBox(currentUnit, p_currentUnitBox);
        updateStatsDisplay(currentUnit, p_currentUnitIcon, 
            p_currentUnitNameText, p_currentUnitHealthText, p_currentUnitEnergyText, 
			p_currentUnitSpeedText, p_currentUnitCombatPointsText);
		
		currentUnit->Redraw();

		currentUnit->UpdateHealthbar();

		return true;
	}
	
	return false;
}

bool Model::attack(glm::ivec2 mouseCoords, TileMap* tileMap, Unit* currentUnit, 
	               std::vector<Unit*> units)
{
	Unit* tarUnit = selectionCheck(units, mouseCoords);
    
	if (tarUnit == nullptr) return false;
	
	Spell* spellToCast = currentUnit->GetMoveSet()->p_spells[m_currentSpellIndex];

	if (spellToCast ->GetCost() <= currentUnit->GetCombatPoints())
	{
		if (checkIfTileReachable(currentUnit->GetCoords(), tarUnit->GetCoords(),
			spellToCast->GetRange()))
		{ 
			SpellType castType = spellToCast->GetType();

			if (currentUnit == tarUnit && SpellType::ATTACK == castType)
			{
			    m_combatLog.announce("WARNING! " + currentUnit->GetName()
				+ " can't attack itself!");
				return false; 
			}

			spellToCast->Cast(currentUnit, tarUnit);
			updateTileStates(tileMap, currentUnit);
	
			updateStatsDisplay(currentUnit, p_currentUnitIcon,
				p_currentUnitNameText, p_currentUnitHealthText,
				p_currentUnitEnergyText, p_currentUnitSpeedText,
				p_currentUnitCombatPointsText);
			updateStatsDisplay(tarUnit, p_selectedUnitIcon,
				p_selectedUnitNameText, p_selectedUnitHealthText,
				p_selectedUnitEnergyText, p_selectedUnitSpeedText,
			    p_selectedUnitCombatPointsText);
			SetSelectedUnit(tarUnit);

			tarUnit->UpdateHealthbar();

			/////////////////////////////
			if (castType == SpellType::ATTACK)
				m_combatLog.announce("EVENT: " + currentUnit->GetName() +
					" hit " + tarUnit->GetName() + " with " + spellToCast->GetName() +
					" for " + std::to_string(spellToCast->GetDamage()) + " damage");
			else if (castType == SpellType::HEAL)
				m_combatLog.announce("EVENT: " + currentUnit->GetName() +
					" healed " + tarUnit->GetName() + " with " + spellToCast->GetName() +
					" for " + std::to_string(spellToCast->GetDamage()) + " health");

			m_visualEffectManager.NewCombatEffect(tarUnit, spellToCast);

			////////////////////////

			if (tarUnit->GetHealth() < 1)
			{
				entityNeedsDeletion(1);
				tarUnit->Death();
				m_combatLog.announce("EVENT! " + tarUnit->GetName() + " has died!");
				SetSelectedUnit(nullptr);
				tileMap->GetTileByCoords(tarUnit->GetCoords())->m_isOccupied = false;
				updateTileStates(tileMap, currentUnit);
			}

			return true;			
		}
	    else m_combatLog.announce("WARNING! " + tarUnit->GetName() + 
            " is out of range of " + 
	        currentUnit->GetName() + "'s " + 
            currentUnit->GetMoveSet()->p_spells[m_currentSpellIndex]
            ->GetName() );
	}
	else m_combatLog.announce("WARNING! " + currentUnit->GetName() +
	   " has no NRG for " + currentUnit->
	   GetMoveSet()->p_spells[m_currentSpellIndex]->GetName());

	return false;
}

void Model::SetSelectedUnit(Unit* selectedUnit)
{
	if (p_selectedUnit != selectedUnit && p_currentUnit != selectedUnit)
	{
		p_selectedUnit = selectedUnit;
		updateStatsDisplay(selectedUnit, p_selectedUnitIcon, 
            p_selectedUnitNameText, p_selectedUnitHealthText, 
            p_selectedUnitEnergyText, p_selectedUnitSpeedText,
			p_selectedUnitCombatPointsText);

		updateSelectedUnitBox(selectedUnit, p_selectionBox);
	}
}

Unit* Model::selectionCheck(std::vector<Unit*> units, glm::ivec2 coords)
{
	for (size_t i = 0; i < units.size(); i++)
		if (units[i]->GetCoords() == coords) return units[i];
	
	return nullptr;
}

void Model::changeSpell(int mode, glm::ivec2 mouseCoords)
{
	switch (mode)
	{
	case 1 :
		if (m_currentSpellIndex > 0) m_currentSpellIndex--;
		break;
	case 0 : 
		m_currentSpellIndex = (m_currentSpellIndex+1) % 4;
		if (p_currentUnit->GetMoveSet()->p_spells[m_currentSpellIndex]->GetCost() == 0)
			 changeSpell(0, mouseCoords);
		break;
	case -1 :
		if (m_currentSpellIndex < 3) m_currentSpellIndex++;
		if (p_currentUnit->GetMoveSet()->p_spells[m_currentSpellIndex]->GetCost() == 0) // no cost means null spell
			changeSpell(1, mouseCoords);
		break;
	}
	
	updateHighlight(p_tileMap->p_tiles, mouseCoords, p_hoverHighlight);
	updateSelectedSpellBox();
}

void Model::updateStatsDisplay(Unit* unit, UIIcon* icon, UIText* name, 
    UIText* health, UIText* energy, UIText* speed, UIText* cb)
{
	//set icon
	if (icon != nullptr) 
	{
		if (unit != nullptr) icon->SetTexture(unit->GetTextureID());
		else icon->SetTexture(-1);

		icon->Redraw();
	}

	//set name
	if (name != nullptr)
	{
		if (unit != nullptr) name->UpdateText(unit->GetName());
		else name->UpdateText("");

		name->Redraw();
	}

	//set health
	if (health != nullptr)
	{
		if (unit != nullptr) 
			health->UpdateText(std::to_string(unit->GetHealth())
                + "/" + std::to_string(unit->GetHealthMax()));
		else health->UpdateText("");

		health->Redraw();
	}

	//set energy
	if (energy != nullptr)
	{
        if (unit != nullptr) 
			energy->UpdateText(std::to_string(unit->GetEnergy()) 
                + "/" + std::to_string(unit->GetEnergyMax()));
		else energy->UpdateText("");

		energy->Redraw();
	}

	if (speed != nullptr)
	{
		if (unit != nullptr)
			speed->UpdateText(std::to_string(unit->GetSpeed()));
		else speed->UpdateText("");

		speed->Redraw();
	}

	if (cb != nullptr)
	{
		if (unit != nullptr)
			cb->UpdateText(std::to_string(unit->GetCombatPoints())
				+ "/" + std::to_string(unit->GetCombatPointsMax()));
		else cb->UpdateText("");

		cb->Redraw();
	}
}

void Model::updateSelectedSpellBox()
{
	p_selectedSpellBox->SetPos(p_spellText[m_currentSpellIndex]->GetPos());
	p_selectedSpellBox->Redraw();
}

void Model::updateSpellDisplay(Unit* currentUnit)
{
	for (size_t i = 0; i < p_spellText.size(); i++)
	{
		if (i < currentUnit->GetMoveSet()->GetMoveSetSize())
		{
			p_spellText[i]->UpdateText(currentUnit->GetMoveSet()->GetSpell(i)->GetName());
			p_spellText[i]->SetVisible(true);
		}
		else
		{
			p_spellText[i]->UpdateText(" ");
			p_spellText[i]->SetVisible(false);
		}
        
		p_spellText[i]->Redraw();
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
			hoverHighlight->SetVisible(true);
			hoverHighlight->SetPos(mouseCoords * TILE_WIDTH);
			hoverHighlight->Redraw();
		}
		else hoverHighlight->SetVisible(false);
	}
    else hoverHighlight->SetVisible(false);
}

void Model::updateHighlightColour(glm::ivec2 mouseCoords, UIIcon* hoverHighlight)
{
	if (checkIfTileReachable(mouseCoords, p_currentUnit->GetCoords(),
		p_currentUnit->GetMoveSet()->p_spells[m_currentSpellIndex]->GetRange()))
		hoverHighlight->SetColour({ 255, 15, 15, 200 });
	else hoverHighlight->SetColour({ 100, 100, 100, 200 });
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
	tileMap->ResetWalkable();
	std::vector<glm::vec2> walkableTiles = tileMap->
		GetWalkablePos(currentUnit->GetCoords(), 
            (int)floor(currentUnit->GetEnergy() / currentUnit->GetMoveCost()));
	p_walkableHighlight->SetMultidraw(walkableTiles);	
	p_walkableHighlight->Redraw();
}

void Model::updateCurrentUnitBox(Unit* currentUnit, UIIcon* currentUnitBox)
{
	if (currentUnit != nullptr)
	{
		currentUnitBox->SetVisible(true);
		currentUnitBox->SetPos(currentUnit->GetPos());
		currentUnitBox->SetColour({ 0, 255, 0, 255 });
	}
	else currentUnitBox->SetVisible(false);

	currentUnitBox->Redraw();
}

void Model::updateSelectedUnitBox(Unit* selectedUnit, UIIcon* selectBox)
{
	if (selectedUnit != nullptr)
	{
		selectBox->SetVisible(true);
		selectBox->SetPos(selectedUnit->GetPos());

        if (selectedUnit->GetIsFriendly()) 
			selectBox->SetColour({ 200, 200, 200, 255 });
		else selectBox->SetColour({ 255, 0, 0, 255 });
	}
	else selectBox->SetVisible(false);

	selectBox->Redraw();
}

Solengine::GameState Model::endTurn(std::vector<Unit*> units, Unit* currentUnit)
{ 
	currentUnit->NewTurn();

	turnCounter = (turnCounter + 1)%units.size();

	for (size_t i = 0; i < units.size(); i++)
		if (units[i]->GetTurnPoints() < currentUnit->GetTurnPoints()) currentUnit = units[i];
	
	beginTurn(units[turnCounter%units.size()]);
	
	return Solengine::GameState::PLAY;
}

void Model::beginTurn(Unit* unit)
{
	SetCurrentUnit(unit);
	m_visualEffectManager.NewCombatEffect(unit, unit->GetStatusEffects());

	if (unit == p_selectedUnit) SetSelectedUnit(nullptr);

	SetCameraCentre(unit);

	updateTileStates(p_tileMap, unit);

	updateCurrentUnitBox(unit, p_currentUnitBox);
	
	updateStatsDisplay(unit, p_currentUnitIcon, p_currentUnitNameText,
		p_currentUnitHealthText, p_currentUnitEnergyText, p_currentUnitSpeedText,
		p_currentUnitCombatPointsText);
	
	m_currentSpellIndex = 0;
	
	updateSpellDisplay(unit);
	
	updateSelectedSpellBox();
}

std::vector<std::pair<Drawable*, Drawable*>> Model::GetEffects() 
{ 
	return m_visualEffectManager.GetEffects();
}