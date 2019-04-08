#include "Controller.h"

Controller::Controller() : m_nextTurn(false)
{
}

Controller::~Controller()
{
}

void Controller::init(Solengine::Camera2D* cam, Model* model)
{
	p_SOL_cam = cam;
	p_model = model;
}

Solengine::GameState Controller::playStateInput()
{
	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;
	const int SCROLL_SPEED = 5;

	Solengine::GameState state = m_SOL_inputManager.processInput();

	if (m_SOL_inputManager.keyPress(SDLK_p))       state = Solengine::GameState::PAUSE;
	if (m_SOL_inputManager.keyPress(SDLK_r))       state = Solengine::GameState::TURNOVER;
	//if (m_SOL_inputManager.keyState(SDLK_q))       p_SOL_cam->setScale(p_SOL_cam->getScale() + SCALE_SPEED);
	//if (m_SOL_inputManager.keyState(SDLK_e))       p_SOL_cam->setScale(p_SOL_cam->getScale() - SCALE_SPEED);
	if (m_SOL_inputManager.keyState(SDLK_w))       p_SOL_cam->shiftPosition(glm::vec2{ 0, SCROLL_SPEED });
	if (m_SOL_inputManager.keyState(SDLK_s))       p_SOL_cam->shiftPosition(glm::vec2{ 0, -SCROLL_SPEED });
	if (m_SOL_inputManager.keyState(SDLK_a))       p_SOL_cam->shiftPosition(glm::vec2{ -SCROLL_SPEED, 0 });
	if (m_SOL_inputManager.keyState(SDLK_d))       p_SOL_cam->shiftPosition(glm::vec2{ SCROLL_SPEED, 0 });

					
	//Check if mousedown occurs where buttons are
	setMouseCoords(m_SOL_inputManager.getMouseCoords());
	setIsMouseDown(m_SOL_inputManager.keyState(SDL_BUTTON_LEFT));

	return state;
}

Unit* Controller::selectionCheck(std::vector<Unit*> units)
{
	glm::vec2 clickWorldPos = p_SOL_cam->screenToWorld(m_mouseCoords);
	for (size_t i = 0; i < units.size(); i++)
	{
		glm::vec2 unitPos = units[i]->getPosition();
	
		if (clickWorldPos.x >= unitPos.x && clickWorldPos.x <= unitPos.x + TILE_WIDTH
			&& clickWorldPos.y >= unitPos.y && clickWorldPos.y <= unitPos.y + TILE_WIDTH)
		{
			return units[i];
		}
	}

	return nullptr;
}

Solengine::GameState Controller::pauseStateInput()
{
	m_SOL_inputManager.processInput();
	Solengine::GameState state = Solengine::GameState::PAUSE;

	if (m_SOL_inputManager.keyPress(SDLK_p))       state = Solengine::GameState::PLAY;

	return state;
}
