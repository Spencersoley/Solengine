#include "Controller.h"

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::init(Solengine::Camera2D* cam)
{
	p_SOL_cam = cam;
}

Solengine::GameState Controller::playStateInput()
{
	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;

	Solengine::GameState state = m_SOL_inputManager.processInput();

	if (m_SOL_inputManager.keyPress(SDLK_p))       state = Solengine::GameState::PAUSE;
	if (m_SOL_inputManager.keyState(SDLK_q))       p_SOL_cam->setScale(p_SOL_cam->getScale() + SCALE_SPEED);
	if (m_SOL_inputManager.keyState(SDLK_e))       p_SOL_cam->setScale(p_SOL_cam->getScale() - SCALE_SPEED);

	return state;
}

Solengine::GameState Controller::pauseStateInput()
{
	m_SOL_inputManager.processInput();
	Solengine::GameState state = Solengine::GameState::PAUSE;

	if (m_SOL_inputManager.keyPress(SDLK_p))       state = Solengine::GameState::PLAY;

	return state;
}
