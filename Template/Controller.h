#pragma once

#include <Solengine/InputManager.h>
#include <Solengine/GameState.h>

#include "View.h"

class Controller
{
public:
	Controller();
	~Controller();

	void init(Solengine::ICamera* cam);
	Solengine::GameState playStateInput();
	Solengine::GameState pauseStateInput();

private:
	Solengine::InputManager m_SOL_inputManager;

	Solengine::ICamera* p_SOL_cam = nullptr;
};

