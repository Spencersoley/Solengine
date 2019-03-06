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

	void init(View* view);

	void initPlayer(Player* player);

	Solengine::GameState processInput();
	
private:
	View* p_view;
	Player* p_player;

	Solengine::InputManager m_SOL_inputManager;
};

