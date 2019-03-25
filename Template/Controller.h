#pragma once

#include <Solengine/InputManager.h>
#include <Solengine/GameState.h>

#include "View.h"

class Controller
{
public:
	Controller();
	~Controller();

	void init(Solengine::Camera2D* cam);
	Solengine::GameState playStateInput();
	Solengine::GameState pauseStateInput();

private:
	Solengine::InputManager m_SOL_inputManager;

	Solengine::Camera2D* p_SOL_cam = nullptr;
};

