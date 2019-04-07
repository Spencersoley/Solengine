#pragma once

#include <Solengine/InputManager.h>
#include <Solengine/GameState.h>

#include "View.h"
#include "Model.h"

class Controller
{
public:
	Controller();
	~Controller();

	void init(Solengine::Camera2D* cam, Model* model);
	Solengine::GameState playStateInput();
	Solengine::GameState pauseStateInput();

	void setMouseCoords(glm::vec2 mouseCoords) { m_mouseCoords = mouseCoords; }
	void setIsMouseDown(bool mouseDown) { m_isMouseDown = mouseDown; }
	bool getIsMouseDown() { return m_isMouseDown; }

	Unit* selectionCheck(std::vector<Unit*> units);

private:
	Solengine::InputManager m_SOL_inputManager;


	Model* p_model;



	glm::vec2 m_mouseCoords;
	bool m_isMouseDown;

	Solengine::Camera2D* p_SOL_cam = nullptr;
};

