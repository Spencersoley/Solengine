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

		void init(int _fpsMax);
		void begin();
		void end(bool track);
		
	private:
		void trackFPS();
		void limitFPS();

		float _trackedFPS;
		int _maxFPS;
		unsigned int _startTicks;

	};
}
