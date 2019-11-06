#pragma once

#include <Solengine/InputManager.h>
#include <Solengine/GameState.h>

#include "View.h"
#include "Player.h"

class Controller
{
public:
	Controller();
	~Controller();

	void init(Solengine::ICamera* cam, Player* player, std::vector<Level*> levels);
	Solengine::GameState playStateInput();
	Solengine::GameState pauseStateInput();

private:
	Solengine::InputManager m_SOL_inputManager;

	std::vector<Level*> p_levels;

	Solengine::ICamera* p_SOL_cam = nullptr;
	Player* p_player = nullptr;
};

