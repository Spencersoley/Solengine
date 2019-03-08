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
		void keyDown(unsigned int keyID);
		void keyUp(unsigned int keyID);
		bool keyPress(unsigned int keyID);
		void setMouseCoords(int x, int y);
		bool keyState(unsigned int keyID);
		bool previousKeyState(unsigned int keyID);
	
	

		Solengine::GameState processInput();

		glm::vec2 getMouseCoords() { return m_mouseCoords; }

	private:
		//We want to store states for all of our keys. We could make an array of booleans, but that would use a lot of memory.
		//Instead, we can use a 'map'. Unordered maps behave similarly to ordered maps except they're internally stored as 
		//a hash table rather than a tree, making it faster to access (it accesses in constant time rather than log time).
		//however, it can use more space than a map. It's fine as order is irrelevant to us.
		void updatePreviousKeyMap();

		std::unordered_map<unsigned int, bool> m_keyMap;
		std::unordered_map<unsigned int, bool> m_previousKeyMap;
		glm::vec2 m_mouseCoords;
	};
}

