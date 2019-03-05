#include "FPSManager.h"

#include <SDL/SDL.h>

namespace Solengine
{
	FPSManager::FPSManager()
	{
	}

	FPSManager::~FPSManager()
	{
	}

	void FPSManager::init(int maxFPS)
	{
		_maxFPS = maxFPS;
	}

	void FPSManager::begin()
	{
		_startTicks = SDL_GetTicks();
	}

	void FPSManager::end(bool track)
	{
	    if (track) trackFPS();
		limitFPS();
	}

	//Announces FPS every NUM_SAMPLES frames
	void FPSManager::trackFPS()
	{
		static const int NUM_SAMPLES = 10;
		static Uint32 frameTimes[NUM_SAMPLES];
		static int frameCount = 0;
		static int announceFrameCount = 0;

		static Uint32 currentTicks;
		static Uint32 prevTicks = SDL_GetTicks();

		//Grabs number of ticks(ms) passed
		currentTicks = SDL_GetTicks();

		//Stores up to 10 samples of milliseconds passed since the previous frame
		frameTimes[frameCount % NUM_SAMPLES] = currentTicks - prevTicks;

		//Stores current milliseconds passed, for next fps calculation
		prevTicks = currentTicks;

		//Sets the number of samples an average frametime can be drawn from
		int limitedFrameCount;
		if (frameCount < NUM_SAMPLES)
		{
			limitedFrameCount = frameCount;
		}
		else
		{
			limitedFrameCount = NUM_SAMPLES;
		}

		//Resets the average frame time
		float frameTimeAverage = 0;

		frameCount++;
		announceFrameCount++;

		//Calculates new average frame time
		for (int i = 0; i < limitedFrameCount; i++)
		{
			frameTimeAverage += frameTimes[i];
		}
		frameTimeAverage /= limitedFrameCount;

		//Sets _fps based on average frame time
		if (frameTimeAverage > 0.0f)
		{
			_trackedFPS = 1000.0f / frameTimeAverage;
		}
		else
		{
			_trackedFPS = 50.0f;
		}

		//Announces fps every 10 cycles
		if (announceFrameCount == 10)
		{
			std::cout << _trackedFPS << std::endl;
			announceFrameCount = 0;
		}
	}

	void FPSManager::limitFPS()
	{
		Uint32 frameTicks = SDL_GetTicks() - _startTicks;
		Uint32 frameTicksLimit = 1000 / _maxFPS;
		//Limit fps to max fps, waiting until it's met before restarting the loop
		if (frameTicksLimit > frameTicks)
		{
			SDL_Delay(frameTicksLimit - frameTicks);
		}
	}
}