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

	void init(Solengine::Camera2D* cam);
	void initPlayer(Player* player); //best practice? what about passing a reference every function call?
	Solengine::GameState playStateInput();
	Solengine::GameState pauseStateInput();

private:
	Solengine::InputManager m_SOL_inputManager;

	Solengine::Camera2D* p_SOL_cam;
	Player* p_player;
};

