#pragma once

#include <SDL/SDL.h>

#include <Solengine/GameState.h>
#include <Solengine/Camera2D.h>
#include <Solengine/InputManager.h>

#include "Unit.h"
#include "UIText.h"
#include "UIButton.h"
#include "UIIcon.h"
#include "CombatLog.h"

class Model
{
public:
	Model();
	~Model();

	void init(float physicsSpeed, Solengine::Camera2D* cam, int sw, int sh);

	void awake(std::vector<Unit*> units);

	Solengine::GameState update(int pauseDuration, std::vector<Unit*> units);
	
	//GETTERS
	bool getLeftMouse() { return m_SOL_inputManager.keyState(SDL_BUTTON_LEFT); }

	bool getRightMouse() { return m_SOL_inputManager.keyState(SDL_BUTTON_RIGHT); }

	glm::ivec2 getMouseScreenInputPos() { return m_SOL_inputManager.getMouseCoords(); }

	glm::ivec2 getMouseScreenPos()  { glm::ivec2 msp = getMouseScreenInputPos(); return { msp.x, m_screenHeight - msp.y }; }

	glm::ivec2 getMouseWorldPos() { return p_SOL_cam->screenToWorld(getMouseScreenInputPos()); }

	glm::ivec2 getMouseCoordinates() { return flatten(getMouseWorldPos(), TILE_WIDTH); }

	glm::ivec2 flatten(glm::ivec2 vec2, int c) { return { floor(vec2.x / c), floor(vec2.y / c) }; }

	CombatLog* getCombatLog() { return &m_combatLog; }

	//SETTERS
	void setSelectedUnit(Unit* unit);

    void setCurrentUnit(Unit* unit) { p_currentUnit = unit; }                   

	void setCurrentUnitIcon(UIIcon* icon) { p_currentUnitIcon = icon; }

	void setCurrentUnitNameText(UIText* text) { p_currentUnitNameText = text; }

	void setCurrentUnitHealthText(UIText* text) { p_currentUnitHealthText = text; }

	void setCurrentUnitEnergyText(UIText* text) { p_currentUnitEnergyText = text; }

	void setCurrentUnitSpeedText(UIText* text) { p_currentUnitSpeedText = text; }

	void setCurrentUnitCombatPointsText(UIText* text) { p_currentUnitCombatPointsText = text; }

	void setCurrentUnitBox(UIIcon* icon) { p_currentUnitBox = icon; }

	void setSelectedUnitIcon(UIIcon* icon) { p_selectedUnitIcon = icon; }

	void setSelectedUnitNameText(UIText* text) { p_selectedUnitNameText = text; }

	void setSelectedHealthText(UIText* text) { p_selectedUnitHealthText = text; }

	void setSelectedEnergyText(UIText* text) { p_selectedUnitEnergyText = text; }

	void setSelectedUnitSpeedText(UIText* text) { p_selectedUnitSpeedText = text; }

	void setSelectedUnitCombatPointsText(UIText* text) { p_selectedUnitCombatPointsText = text; }

    // These get pushed back in order
	void setSpellText(UIText* text) { p_spellText.push_back(text); }

	void setSelectionBox(UIIcon* icon) { p_selectionBox = icon; }
	
	void setSelectedSpellBox(UIIcon* icon) { p_selectedSpellBox = icon; }

	void setHoverHighlight(UIIcon* icon) { p_hoverHighlight = icon; }

    void setWalkableHighlight(UIIcon* icon) { p_walkableHighlight = icon; }

	void setTileMap(TileMap* tileMap) { p_tileMap = tileMap; }

	void setCombatLog(std::vector<UIText*> texts) { m_combatLog.setTexts(texts); }

	void setScrollIcon(UIIcon* icon) { m_combatLog.setScrollIcon(icon); }

	std::vector<Drawable*> getEffects();

	bool deleteCheck() { return m_entityNeedsDeletion; }


private:
	Solengine::InputManager m_SOL_inputManager;
	Solengine::Camera2D* p_SOL_cam;
	CombatLog m_combatLog;

	std::vector<Drawable*> p_visualEffects;
	std::vector<UIElement*> p_mouseoverable;

	int  m_screenHeight;
	int m_screenWidth;
	int m_currentSpellIndex = 0;

	void changeSpell();
	void entityNeedsDeletion(bool set) { m_entityNeedsDeletion = set; }
	void updateSelectedSpellBox();
	
	Unit* p_selectedUnit = nullptr;
	Unit* p_currentUnit = nullptr;

	UIIcon* p_currentUnitIcon = nullptr;
	UIText* p_currentUnitNameText = nullptr;
	UIText* p_currentUnitHealthText = nullptr;
    UIText* p_currentUnitEnergyText = nullptr;
	UIText* p_currentUnitSpeedText = nullptr;
	UIText* p_currentUnitCombatPointsText = nullptr;
    UIIcon* p_currentUnitBox = nullptr;
	
	UIIcon* p_selectedUnitIcon = nullptr;
	UIText* p_selectedUnitNameText = nullptr;
	UIText* p_selectedUnitHealthText = nullptr;
	UIText* p_selectedUnitEnergyText = nullptr;
	UIText* p_selectedUnitSpeedText = nullptr;
	UIText* p_selectedUnitCombatPointsText = nullptr;
	UIIcon* p_selectionBox = nullptr;

	UIIcon* p_selectedSpellBox = nullptr;
	
	std::vector<UIText*> p_spellText;

	UIIcon* p_walkableHighlight = nullptr;
	UIIcon* p_hoverHighlight = nullptr;
	TileMap* p_tileMap;

	// used in 'deleteCheck()' function
	bool m_entityNeedsDeletion = false; 
	int m_turnCounter;
	float m_physicsSpeed;
	
	Uint32 getDeltaTicks();
	bool movement(glm::ivec2 coords, TileMap* tileMap, Unit* currentUnit);
	bool attack(glm::ivec2 coords, TileMap* tileMap, Unit* currentUnit, std::vector<Unit*> units);
	Solengine::GameState nextTurn(std::vector<Unit*> units, Unit* currentUnit, 
        Unit* selectedUnit);
	Unit* selectionCheck(std::vector<Unit*> units, glm::ivec2 coords);

	void updateHighlight(std::vector<std::vector<Tile*>> tiles,
        glm::ivec2 mouseCoords, UIIcon* hoverHighlight);
	void updateHighlightColour(glm::ivec2 mouseCoords, UIIcon* hoverHighlight);
	bool checkIfTileReachable(glm::ivec2 mouseCoords, glm::ivec2 unitCoords, int spellRange);

	bool checkIfCoordsInBound(std::vector<std::vector<Tile*>> tiles, 
        glm::ivec2 coords);
	void updateTileStates(TileMap* tileMap, Unit* currentUnit);
	void updateStatsDisplay(Unit* unit, UIIcon* icon, UIText* name,
        UIText* health, UIText* energy, UIText* speed, UIText* cb);
	void updateSelectedUnitBox(Unit* selectedUnit, UIIcon* selectionBox);
    void updateCurrentUnitBox(Unit* currentUnit, UIIcon* currentUnitBox);
	void updateSpellDisplay(Unit* currentUnit);

};