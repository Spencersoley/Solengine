#include "SDLInitialiser.h"

#include <SDL/SDL.h>
#include <GL/glew.h>

namespace Solengine
{
	int sdlInit()
	{
		//Initialise SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		//Tells SDL we want a double buffered window to prevent flickering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}
}