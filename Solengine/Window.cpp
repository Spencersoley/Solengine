#include "Window.h"

#include "ErrorManager.h"

namespace Solengine
{
	Window::Window()
	{
	}

	Window::~Window()
	{
	}

	int Window::Create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlags & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		//Open an SDL window
		p_SdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
		if (p_SdlWindow == nullptr)
		{
			ErrorManager::FatalError("SDL Window could not be created!");
		}

		//Set up OpenGL context
		SDL_GLContext glContext = SDL_GL_CreateContext(p_SdlWindow);
		if (glContext == nullptr)
		{
			ErrorManager::FatalError("SDL_GL context could not be created!");
		}

		//Set up glew
		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			ErrorManager::FatalError("Could not initialise GLEW");
		}

		//Check openGL version
		std::printf("**** OpenGL Version: %s ***\n", glGetString(GL_VERSION));

		//Background Colour
		//glClearColor(0.4f, 1.0f, 1.0f, 1.0f);

		//VSYNC
		SDL_GL_SetSwapInterval(0);
		
		//Enable alpha blend
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::SwapBuffer()
	{
		if (p_SdlWindow == nullptr)
		{
			ErrorManager::FatalError("SDL Window could not be swapped!");
		}
		SDL_GL_SwapWindow(p_SdlWindow);
	}
}