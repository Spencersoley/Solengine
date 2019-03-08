#include "Controller.h"

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::init(View* view)
{
	p_view = view;
}

void Controller::initPlayer(Player* player)
{
	p_player = player;
}

Solengine::GameState Controller::playStateInput()
{
	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;

	Solengine::GameState state = m_SOL_inputManager.processInput();
	if (m_SOL_inputManager.keyState(SDLK_w))  ///
	{
		p_player->setYDir(1);
	}

	if (m_SOL_inputManager.keyState(SDLK_s))  ///
	{
		p_player->setYDir(-1);
	}

	if (m_SOL_inputManager.keyState(SDLK_d)) ///
	{
		p_player->setXDir(1);
	}

	if (m_SOL_inputManager.keyState(SDLK_a))  ///
	{
		p_player->setXDir(-1);
	}

	if ((m_SOL_inputManager.keyState(SDLK_1) && (p_player->getNumOfGuns()) > 0))
	{
		p_player->setCurrentGunIndex(0);
	}

	if ((m_SOL_inputManager.keyState(SDLK_2) && (int)(p_player->getNumOfGuns()) >= 1))
	{
		p_player->setCurrentGunIndex(1);
	}

	if ((m_SOL_inputManager.keyState(SDLK_3) && (int)(p_player->getNumOfGuns()) >= 2))
	{
		p_player->setCurrentGunIndex(2);
	}

	if (m_SOL_inputManager.keyPress(SDLK_p))
	{
		state = Solengine::GameState::PAUSE; 
	}

	if (m_SOL_inputManager.keyState(SDLK_q))
	{
		p_view->scale(SCALE_SPEED);
	}

	if (m_SOL_inputManager.keyState(SDLK_e))
	{
		p_view->scale(-SCALE_SPEED);
	}

	p_player->setMouseCoords(m_SOL_inputManager.getMouseCoords());  
	p_player->setIsMouseDown(m_SOL_inputManager.keyState(SDL_BUTTON_LEFT));

	return state;
}

Solengine::GameState Controller::pauseStateInput()
{
	m_SOL_inputManager.processInput();
	Solengine::GameState state = Solengine::GameState::PAUSE;

	//This needs to check keydown

	if (m_SOL_inputManager.keyPress(SDLK_p))
	{
		state = Solengine::GameState::PLAY;
	}

	return state;
}
