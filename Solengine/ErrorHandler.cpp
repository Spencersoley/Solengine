#include "ErrorHandler.h"

#include <cstdlib>
#include <iostream>
#include <SDL/SDL.h>

namespace Solengine
{
	void fatalError(std::string errorString)
	{
		std::cout << errorString << std::endl;
		std::cout << "Enter any key to quit...";
		int temp;
		std::cin >> temp;
		SDL_Quit();
		exit(1);
    }
}
