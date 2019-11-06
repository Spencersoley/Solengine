#include "Controller.h"

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::init(Solengine::ICamera* cam, Player* player, std::vector<Level*> levels)
{
	p_SOL_cam = cam;
	p_player = player;
	p_levels = levels;
}

Solengine::GameState Controller::playStateInput()
{
	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;

	Solengine::GameState state = m_SOL_inputManager.processInput();
	
	if (m_SOL_inputManager.keyState(SDLK_w))       p_player->setYDir(1);
	if (m_SOL_inputManager.keyState(SDLK_s))       p_player->setYDir(-1);
	if (m_SOL_inputManager.keyState(SDLK_d))       p_player->setXDir(1);
	if (m_SOL_inputManager.keyState(SDLK_a))       p_player->setXDir(-1);
	if (m_SOL_inputManager.keyState(SDLK_1))       p_player->setCurrentGunIndex(0);
    if (m_SOL_inputManager.keyState(SDLK_2))       p_player->setCurrentGunIndex(1);
	if (m_SOL_inputManager.keyState(SDLK_3))       p_player->setCurrentGunIndex(2);
	if (m_SOL_inputManager.keyPress(SDLK_p))       state = Solengine::GameState::PAUSE; 
	if (m_SOL_inputManager.keyState(SDLK_q))       p_SOL_cam->setScale(p_SOL_cam->getScale() + SCALE_SPEED);
	if (m_SOL_inputManager.keyState(SDLK_e))       p_SOL_cam->setScale(p_SOL_cam->getScale() - SCALE_SPEED);

	p_player->setMouseCoords(m_SOL_inputManager.getMouseCoords());  
	p_player->setIsMouseDown(m_SOL_inputManager.keyState(SDL_BUTTON_LEFT));

	return state;
}

Solengine::GameState Controller::pauseStateInput()
{
	m_SOL_inputManager.processInput();
	Solengine::GameState state = Solengine::GameState::PAUSE;

	if (m_SOL_inputManager.keyPress(SDLK_p))       state = Solengine::GameState::PLAY;

	return state;
}
