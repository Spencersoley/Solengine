#pragma once

#include <SDL/SDL.h>

#include <unordered_map>
#include <glm/glm.hpp>

#include "GameState.h"

namespace Solengine {
//Checks for inputs, changes keystates
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		//Using SDL keyIDs for now, would be better to wrap keyIDs in your own enum
		void KeyDown(unsigned int keyID);
		void KeyUp(unsigned int keyID);
		bool KeyPress(unsigned int keyID);
		void SetMouseCoords(int x, int y);
		void SetMouseWheel(float y);
		bool KeyState(unsigned int keyID);
		bool PreviousKeyState(unsigned int keyID);

		Solengine::GameState ProcessInput();

		glm::vec2 GetMouseCoords() { return m_mouseCoords; }
		float GetMouseWheel() { return m_mouseWheel; }

	private:
		void updatePreviousKeyMap();

		std::unordered_map<unsigned int, bool> m_keyMap;
		std::unordered_map<unsigned int, bool> m_previousKeyMap;
		glm::vec2 m_mouseCoords;
		float m_mouseWheel;
	};
}

