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

class View
{
public:
	View();
	~View();

	void init(Solengine::Camera2D* cam, Solengine::Camera2D* uiCam, int screenWidth, int screenHeight);
	void update(std::vector<Level*>& levels, std::vector<Unit*>& units, std::vector<UIElement*>& uiElements, Unit* currentUnit, Unit* selectedUnit);

private:
	void drawGame(std::vector<Level*>& levels, std::vector<Unit*>& units, std::vector<UIElement*>& uiElements, Unit* currentUnit, Unit* selectedUnit);

	void drawUI(std::vector<UIElement*>& uiElements, Unit* currentUnit, Unit* selectedUnit);


	void drawWorld(std::vector<Level*>& levels, std::vector<Unit*>& units);
	void drawLevel(std::vector<Level*>& levels);
	void drawUnits(std::vector<Unit*>& units);

	Solengine::GLSLProgram m_SOL_shaderProgram;
	Solengine::Window m_SOL_window;


	//Every separate sprite has its own sprite batch.

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