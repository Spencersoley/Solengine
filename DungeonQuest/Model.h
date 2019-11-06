#pragma once

#include <SDL/SDL.h>

#include <Solengine/GameState.h>
#include <Solengine/ICamera.h>
#include <Solengine/InputManager.h>

#include "Unit.h"
#include "UIText.h"
#include "UIButton.h"
#include "UIIcon.h"
#include "CombatLog.h"
#include "VisualEffectManager.h"

class Model
{
public:
	Model();
	~Model();

	void Init(float physicsSpeed, Solengine::ICamera* cam, int sw, int sh);

	void Awake(std::vector<Unit*> units);

	Solengine::GameState Update(int pauseDuration, std::vector<Unit*> units);
	
	//GETTERS
	bool GetLeftMouse() { return m_SOL_inputManager.KeyState(SDL_BUTTON_LEFT); }

	bool GetRightMouse() { return m_SOL_inputManager.KeyState(SDL_BUTTON_RIGHT); }

	glm::ivec2 GetMouseScreenInputPos() { return m_SOL_inputManager.GetMouseCoords(); }

	glm::ivec2 GetMouseScreenPos()  { glm::ivec2 msp = GetMouseScreenInputPos(); return { msp.x, m_screenHeight - msp.y }; }

	glm::ivec2 GetMouseWorldPos() { return p_SOL_cam->ScreenToWorld(GetMouseScreenInputPos()); }

	glm::ivec2 GetMouseCoordinates() { return Flatten(GetMouseWorldPos(), TILE_WIDTH); }

	float GetMouseWheel() { return m_SOL_inputManager.GetMouseWheel(); }

	glm::ivec2 Flatten(glm::ivec2 vec2, int c) { return { floor(vec2.x / c), floor(vec2.y / c) }; }

	CombatLog* GetCombatLog() { return &m_combatLog; }

	//SETTERS
	void SetCameraCentre(Drawable* drawable) { p_SOL_cam->SetPosition(drawable->GetPos() - glm::vec2(0.5f * TILE_WIDTH, 0.5f * TILE_WIDTH)); }

	void SetSelectedUnit(Unit* unit);

	void SetCurrentUnit(Unit* unit) { p_currentUnit = unit; }

	void SetCurrentUnitIcon(UIIcon* icon) { p_currentUnitIcon = icon; }

	void SetCurrentUnitNameText(UIText* text) { p_currentUnitNameText = text; }

	void SetCurrentUnitHealthText(UIText* text) { p_currentUnitHealthText = text; }

	void SetCurrentUnitEnergyText(UIText* text) { p_currentUnitEnergyText = text; }

	void SetCurrentUnitSpeedText(UIText* text) { p_currentUnitSpeedText = text; }

	void SetCurrentUnitCombatPointsText(UIText* text) { p_currentUnitCombatPointsText = text; }

	void SetCurrentUnitBox(UIIcon* icon) { p_currentUnitBox = icon; }

	void SetSelectedUnitIcon(UIIcon* icon) { p_selectedUnitIcon = icon; }

	void SetSelectedUnitNameText(UIText* text) { p_selectedUnitNameText = text; }

	void SetSelectedHealthText(UIText* text) { p_selectedUnitHealthText = text; }

	void SetSelectedEnergyText(UIText* text) { p_selectedUnitEnergyText = text; }

	void SetSelectedUnitSpeedText(UIText* text) { p_selectedUnitSpeedText = text; }

	void SetSelectedUnitCombatPointsText(UIText* text) { p_selectedUnitCombatPointsText = text; }

    // These get pushed back in order
	void SetSpellText(UIText* text) { p_spellText.push_back(text); }

	void SetSelectionBox(UIIcon* icon) { p_selectionBox = icon; }
	
	void SetSelectedSpellBox(UIIcon* icon) { p_selectedSpellBox = icon; }

	void SetHoverHighlight(UIIcon* icon) { p_hoverHighlight = icon; }

    void SetWalkableHighlight(UIIcon* icon) { p_walkableHighlight = icon; }

	void SetTileMap(TileMap* tileMap) { p_tileMap = tileMap; }

	void SetCombatLog(std::vector<UIText*> texts) { m_combatLog.setTexts(texts); }

	void SetScrollIcon(UIIcon* icon) { m_combatLog.setScrollIcon(icon); }

	void SetUIPanelHeight(int h) { m_UIpanelHeight = h; }

	std::vector<std::pair<Drawable*, Drawable*>> GetEffects();

	bool DeleteCheck() 
	{ 
		if (m_entityNeedsDeletion) { entityNeedsDeletion(0); return true; }
		return false; 
	}


private:
	Solengine::InputManager m_SOL_inputManager;
	Solengine::ICamera* p_SOL_cam;
	CombatLog m_combatLog;

	VisualEffectManager m_visualEffectManager;

	std::vector<Drawable*> p_visualEffects;
	std::vector<UIElement*> p_mouseoverable;

	int  m_screenHeight;
	int m_screenWidth;
	int m_currentSpellIndex = 0;

	void changeSpell(int mode, glm::ivec2 mouseCoords);
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

	int m_UIpanelHeight = 0;
	
	std::vector<UIText*> p_spellText;

	UIIcon* p_walkableHighlight = nullptr;
	UIIcon* p_hoverHighlight = nullptr;
	TileMap* p_tileMap;

	// used in 'deleteCheck()' function
	bool m_entityNeedsDeletion = false; 
	int m_turnCounter;
	float m_physicsSpeed;
	

	void beginTurn(Unit* unit);

	Uint32 getDeltaTicks();
	bool movement(glm::ivec2 coords, TileMap* tileMap, Unit* currentUnit);
	bool attack(glm::ivec2 coords, TileMap* tileMap, Unit* currentUnit, std::vector<Unit*> units);
	Solengine::GameState endTurn(std::vector<Unit*> units, Unit* currentUnit);
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

	unsigned int turnCounter;
};