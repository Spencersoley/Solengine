#pragma once

#include <iostream>
#include <SDL/SDL.h>
#include <GL/glew.h>

namespace Solengine
{
	class FPSManager
	{
	public:
		FPSManager();
		~FPSManager();

		void limitFPS(bool track, int desiredFrameTicks);
		
	private:
		void trackFPS();

		int m_FPSMax;
		unsigned int m_startTicks;
	};
}
