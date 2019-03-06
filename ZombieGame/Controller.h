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
	View* _view;
	Player* _player;

	Solengine::InputManager _SOL_inputManager;
};

