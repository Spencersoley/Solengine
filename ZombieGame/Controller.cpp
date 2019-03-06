#include "Controller.h"

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::init(View* view)
{
	_view = view;
}

void Controller::initPlayer(Player* player)
{
	_player = player;
	_player->initInputManager(&_SOL_inputManager);
}

Solengine::GameState Controller::processInput()
{
	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;

	Solengine::GameState state = _SOL_inputManager.processInput();

	if (_SOL_inputManager.key(SDLK_q))
	{
		_view->scale(SCALE_SPEED);
	}
	if (_SOL_inputManager.key(SDLK_e))
	{
		_view->scale(-SCALE_SPEED);
	}

	return state;
}
