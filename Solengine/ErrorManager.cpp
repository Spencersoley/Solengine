#include "ErrorManager.h"

#include <iostream>
#include <SDL\SDL.h>

namespace Solengine
{
	void ErrorManager::FatalError(std::string errorString)
	{
		std::cout << errorString << std::endl;
		std::cout << "Enter any key to quit...";
		int temp;
		std::cin >> temp;
		SDL_Quit();
		exit(1);
    }
}
