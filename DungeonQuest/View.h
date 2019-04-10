#pragma once

#include <Solengine/GLSLProgram.h>
#include <Solengine/Camera2D.h>
#include <Solengine/SpriteBatch.h>
#include <Solengine/Window.h>
#include <Solengine/Font.h>

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

//add drawing level by default to template
#include "Level.h"
#include "Unit.h"
#include "UIElement.h"
#include "UIText.h"
#include "UIButton.h"
#include "UIIcon.h"

#include "Controller.h"

class View
{
public:
	View();
	~View();

	void init(Controller* controller, Solengine::Camera2D* cam, Solengine::Camera2D* uiCam, int screenWidth, int screenHeight);
	void update(std::vector<Level*>& levels, std::vector<Unit*>& units, std::vector<UIElement*>& uiElements, Unit* currentUnit, Unit* selectedUnit);

	void setCurrentUnitNameTextBox(UIText* currentUnitNameTextBox) { p_currentUnitNameTextBox = currentUnitNameTextBox; }
	void setCurrentUnitIcon(UIIcon* currentUnitIcon) { p_currentUnitIcon = currentUnitIcon;  }
	void setSelectedUnitNameTextBox(UIText* selectedUnitNameText) { p_selectedUnitNameTextBox = selectedUnitNameText; }
	void setSelectedUnitIcon(UIIcon* selectedUnitIcon) { p_selectedUnitIcon = selectedUnitIcon; }
	void setSelectionBox(UIIcon* selectionBox) { p_selectionBox = selectionBox; }
	void setCurrentUnitBox(UIIcon* currentUnitBox) { p_currentUnitBox = currentUnitBox; }
	void setCurrentEnergyText(UIText* currentEnergyText) { p_currentEnergyText = currentEnergyText; }
	void setCurrentHealthText(UIText* currentHealthText) { p_currentHealthText = currentHealthText; }
	void setSelectedHealthText(UIText* selectedHealthText) { p_selectedHealthText = selectedHealthText; }
	void setSelectedEnergyText(UIText* selectedEnergyText) { p_selectedEnergyText = selectedEnergyText;  }
	void setMouseOverHighlight(UIIcon* mouseOverHighlight) { p_mouseOverHighlight = mouseOverHighlight;  }
	void setTileMap(TileMap* tileMap) { p_tileMap = tileMap; }

private:
	void drawGame(std::vector<Level*>& levels, std::vector<Unit*>& units, std::vector<UIElement*>& uiElements, Unit* currentUnit, Unit* selectedUnit);

	void drawUI(std::vector<UIElement*>& uiElements, Unit* currentUnit, Unit* selectedUnit);


	void drawWorld(std::vector<Level*>& levels, std::vector<Unit*>& units, Unit* currentUnit, Unit* selectedUnit);
	void drawLevel(std::vector<Level*>& levels);
	void drawUnits(std::vector<Unit*>& units);
	void drawWorldspaceUI(Unit* currentUnit, Unit* selectedUnit);

	Controller* p_controller = nullptr;

	Solengine::GLSLProgram m_SOL_shaderProgram;
	Solengine::Window m_SOL_window;

	UIText* p_currentUnitNameTextBox = nullptr;
	UIIcon* p_currentUnitIcon = nullptr;
	UIText* p_selectedUnitNameTextBox = nullptr;
	UIIcon* p_selectedUnitIcon = nullptr;
	UIIcon* p_selectionBox = nullptr;
	UIIcon* p_currentUnitBox = nullptr;
	UIText* p_currentEnergyText = nullptr;
	UIText* p_currentHealthText = nullptr;
	UIText* p_selectedHealthText = nullptr;
	UIText* p_selectedEnergyText = nullptr;
	UIIcon* p_mouseOverHighlight = nullptr;

	TileMap* p_tileMap = nullptr;

	Solengine::Font* p_SOL_spriteFont;
	
	Solengine::Camera2D* p_SOL_cam = nullptr;
	Solengine::Camera2D* p_SOL_uiCam = nullptr;

	int m_screenHeight;
	int m_screenWidth;
	int m_currentLevel;
};

//(2) update function, called from scene
// Scene to call 'update content and render' every frame
// Scene to call 'update statistics' only when they need updating. This is ideal, but we won't do this for now.
// public update(levels, units, buttons)
// scene calls view.update(levels, units, ui objects) -->  view calls drawWorld(levels, units)
//                                                    -->  view calls drawUI(p_UIElements),
// /////Ui elements (ABC): buttons override, text boxes override
// /////UIManager class? create the ui elements
// drawWorld ---> drawUnits
//           ---> drawLevel
// drawUI    ---> drawUIElements
//           ---> drawUIBackground