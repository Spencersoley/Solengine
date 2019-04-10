#pragma once

#include <Solengine/InputManager.h>
#include <Solengine/GameState.h>
#include <Solengine/Camera2D.h>

#include "Model.h"

class Controller
{
public:
	Controller();
	~Controller();

	void init(Solengine::Camera2D* cam, Model* model);
	Solengine::GameState playStateInput(Unit* p_currentUnit);
	Solengine::GameState pauseStateInput();

	void setMousePos(glm::vec2 mousePos) { m_mousePos = mousePos; }
	glm::vec2 getMouseScreenPos() { return m_mousePos; }
	glm::vec2 getMouseWorldPos() { return p_SOL_cam->screenToWorld(m_mousePos); }
	void setIsMouseDown(bool mouseDown) { m_isMouseDown = mouseDown; }
	bool getIsMouseDown() { return m_isMouseDown; }


	Unit* selectionCheck(std::vector<Unit*> units);

private:
	Solengine::InputManager m_SOL_inputManager;

	Model* p_model;

	int* p_turnCounter;

	glm::vec2 m_mousePos;
	bool m_isMouseDown;
	bool m_nextTurn;

	Solengine::Camera2D* p_SOL_cam = nullptr;
};

