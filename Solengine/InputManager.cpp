#include "InputManager.h"

#include <iostream>

//Only currently has functionality for recognising whether a key is down.
//Potential to add specific feature on key down.

namespace Solengine {

	InputManager::InputManager() : m_mouseCoords(0)
	{
	}

	InputManager::~InputManager()
	{
	}

	//Checks all queued events, changing their states accordingly
	Solengine::GameState InputManager::processInput()
	{
		setMouseWheel(0);
		updatePreviousKeyMap();

		SDL_Event evnt;

		while (SDL_PollEvent(&evnt))
		{
			switch (evnt.type)
			{
			case SDL_QUIT:
				return Solengine::GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				setMouseCoords(evnt.motion.x, evnt.motion.y);
				break;
			case SDL_MOUSEBUTTONDOWN:
				keyDown(evnt.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				keyUp(evnt.button.button);
				break;
			case SDL_MOUSEWHEEL:
				setMouseWheel(evnt.wheel.y);
			case SDL_KEYDOWN:
				keyDown(evnt.key.keysym.sym);
				break;
			case SDL_KEYUP:
				keyUp(evnt.key.keysym.sym);
				break;
			}
		}

		return Solengine::GameState::PLAY;
	}

	//Copies the previous key states into a new map
	void InputManager::updatePreviousKeyMap()
	{
		for (auto& it : m_keyMap)
		{
			m_previousKeyMap[it.first] = it.second;
		}
	}

	//Changes the state of the key in the current map
	void InputManager::keyDown(unsigned int keyID)
	{
		//Creates a pair if it doesn't exist in the map
		m_keyMap[keyID] = true;
	}

	//Changes the state of the key in the current map
	void InputManager::keyUp(unsigned int keyID)
	{
		m_keyMap[keyID] = false;
	}

	//Returns the state of the key id in the current map
	bool InputManager::keyState(unsigned int keyID)
	{
		auto it = m_keyMap.find(keyID);
		
		if (it != m_keyMap.end()) 
		{
			//'second' returns the second value in a pair
			return it->second;
		}
		else
		{
			return false;
		}
	}

	//Returns the state of the key id in the previous map
	bool InputManager::previousKeyState(unsigned int keyID)
	{
		auto it = m_previousKeyMap.find(keyID);

		if (it != m_previousKeyMap.end())
		{
			return it->second;
		}
		else
		{
			return false;
		}
	}

	//checks for a key press
	bool InputManager::keyPress(unsigned int keyID) 
	{
		if (keyState(keyID) && !previousKeyState(keyID))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void InputManager::setMouseCoords(int x, int y) 
	{
		m_mouseCoords.x = (float)x;
		m_mouseCoords.y = (float)y;
	}

	void InputManager::setMouseWheel(float y)
	{
		m_mouseWheel = (float)y;
	}
}