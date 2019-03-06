#include "InputManager.h"

#include <iostream>

//Only currently has functionality for recognising whether a key is down.
//Potential to add specific feature on key down.

namespace Solengine {

	InputManager::InputManager() : _mouseCoords(0)
	{
	}

	InputManager::~InputManager()
	{
	}

	//Edits the keyMap
	void InputManager::keyDown(unsigned int keyID)
	{
		//checks if keyID is in the map. If not, it creates it. Then sets it to true.
		_keyMap[keyID] = true;
	}

	void InputManager::keyUp(unsigned int keyID)
	{
		_keyMap[keyID] = false;
	}

	//Checks the keymap
	bool InputManager::key(unsigned int keyID)
	{
		auto it = _keyMap.find(keyID);
		
		//.end returns true if key 'it' is not in the map
		//this bool returns true if 'it' is in the map
		if (it != _keyMap.end()) 
		{
			//function returns the (as a boolean) second value in the pair 'it' is in
			return it->second;
		}
		else
		{
			return false;
		}
	}

	void InputManager::setMouseCoords(int x, int y) 
	{
		_mouseCoords.x = (float)x;
		_mouseCoords.y = (float)y;
	}

}