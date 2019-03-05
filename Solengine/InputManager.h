#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

//Could be expanded to allow for choosing your own hotkeys

namespace Solengine {

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		//Using SDL keyIDs for now, would be better to wrap keyIDs in your own enum
		void keyDown(unsigned int keyID);
		void keyUp(unsigned int keyID);
		void setMouseCoords(int x, int y);
		bool key(unsigned int keyID);

		glm::vec2 getMouseCoords() { return _mouseCoords; }

	private:
		//We want to store states for all of our keys. We could make an array of booleans, but that would use a lot of memory.
		//Instead, we can use a 'map'. Unordered maps behave similarly to ordered maps except they're internally stored as 
		//a hash table rather than a tree, making it faster to access (it accesses in constant time rather than log time).
		//however, it can use more space than a map. It's fine as order is irrelevant to us.

		std::unordered_map<unsigned int, bool> _keyMap;
		glm::vec2 _mouseCoords;
	};
}

