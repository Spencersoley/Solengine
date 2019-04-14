#pragma once

#include <SDL/SDL.h>
#include <Solengine/GameState.h>
#include <Solengine/Camera2D.h>
#include <Solengine/InputManager.h>
//#include <GL/glew.h>
//#include <vector>
//#include <glm/glm.hpp>
#include "Unit.h"
#include "UIElement.h"
#include "UIText.h"
#include "UIButton.h"
#include "UIIcon.h"

class Model
{
public:
	Model();
	~Model();

	void init(float physicsSpeed, Solengine::Camera2D* cam);
	Solengine::GameState update(int pauseDuration, std::vector<Unit*> units);

	bool getLeftMouse() { return m_SOL_inputManager.keyState(SDL_BUTTON_LEFT); }
	bool getRightMouse() { return m_SOL_inputManager.keyState(SDL_BUTTON_RIGHT); }
	glm::ivec2 getMouseScreenPosition() { return m_SOL_inputManager.getMouseCoords(); }
	glm::ivec2 getMouseWorldPosition() { return p_SOL_cam->screenToWorld(getMouseScreenPosition()); }
	glm::ivec2 getMouseCoordinates() { return { floor(getMouseWorldPosition().x / 64), floor(getMouseWorldPosition().y / 64) }; }

	//
	void setSelectedUnit(Unit* unit);
	void setCurrentUnit(Unit* unit) { p_currentUnit = unit; }

	//ui

	void setCurrentUnitIcon(UIIcon* currentUnitIcon) { p_currentUnitIcon = currentUnitIcon; }
	void setCurrentUnitNameTextBox(UIText* currentUnitNameTextBox) { p_currentUnitNameTextBox = currentUnitNameTextBox; }
	void setCurrentUnitHealthText(UIText* currentUnitHealthText) { p_currentUnitHealthText = currentUnitHealthText; }
	void setCurrentUnitEnergyText(UIText* currentUnitEnergyText) { p_currentUnitEnergyText = currentUnitEnergyText; }
	void setCurrentUnitBox(UIIcon* currentUnitBox) { p_currentUnitBox = currentUnitBox; }

	void setSelectedUnitIcon(UIIcon* selectedUnitIcon) { p_selectedUnitIcon = selectedUnitIcon; }
	void setSelectedUnitNameTextBox(UIText* selectedUnitNameText) { p_selectedUnitNameTextBox = selectedUnitNameText; }
	void setSelectedHealthText(UIText* selectedUnitHealthText) { p_selectedUnitHealthText = selectedUnitHealthText; }
	void setSelectedEnergyText(UIText* selectedUnitEnergyText) { p_selectedUnitEnergyText = selectedUnitEnergyText; }
	void setSelectionBox(UIIcon* selectionBox) { p_selectionBox = selectionBox; }

	void setHoverHighlight(UIIcon* hoverHighlight) { p_hoverHighlight = hoverHighlight; }
	void setWalkableHighlight(UIIcon* walkableHighlight) { p_walkableHighlight = walkableHighlight; }
	void setTileMap(TileMap* tileMap) { p_tileMap = tileMap; }

private:
	Solengine::InputManager m_SOL_inputManager;
	Solengine::Camera2D* p_SOL_cam;
	
	Unit* p_selectedUnit = nullptr;
	Unit* p_currentUnit = nullptr;

	UIText* p_currentUnitHealthText = nullptr;
    UIText* p_currentUnitEnergyText = nullptr;
	UIIcon* p_currentUnitIcon = nullptr;
	UIText* p_currentUnitNameTextBox = nullptr;
    UIIcon* p_currentUnitBox = nullptr;
	
	UIIcon* p_selectedUnitIcon = nullptr;
	UIText* p_selectedUnitNameTextBox = nullptr;
	UIText* p_selectedUnitHealthText = nullptr;
	UIText* p_selectedUnitEnergyText = nullptr;
	UIIcon* p_selectionBox = nullptr;
	
	UIIcon* p_walkableHighlight = nullptr;
	UIIcon* p_hoverHighlight = nullptr;
	TileMap* p_tileMap;

	int m_turnCounter;

	float m_physicsSpeed;
	
	Uint32 getDeltaTicks();
	void attemptMovement(glm::vec2 coords);
	Solengine::GameState nextTurn(std::vector<Unit*> units);
	Unit* selectionCheck(std::vector<Unit*> units);
	void updateStatsDisplay(Unit* unit, UIIcon* icon, UIText* name, UIText* health, UIText* energy);
	void highlightTile(std::vector<std::vector<Tile*>> tiles);
	bool checkIfCoordsInBound(std::vector<std::vector<Tile*>> tiles, glm::ivec2 coords);
	void setWalkableTiles(TileMap* tileMap, Unit* currentUnit);
};