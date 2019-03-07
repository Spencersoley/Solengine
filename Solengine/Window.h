#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>

namespace Solengine
{
	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Window
	{
	public:
		Window();
		~Window();

		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

		void swapBuffer();

		int getScreenHeight() { m_screenHeight; }
		int getScreenWidth() { m_screenWidth; }
	private:
		SDL_Window* p_SdlWindow;
		int m_screenWidth, m_screenHeight;
	};
}

