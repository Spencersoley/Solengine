#include "FPSManager.h"

#include <SDL/SDL.h>
#include <algorithm>

namespace Solengine
{
	FPSManager::FPSManager()
	{
	}

	FPSManager::~FPSManager()
	{
	}

	void FPSManager::LimitFPS(bool track, Uint32 desiredFrameTicks)
	{
		Uint32 frameTicks = SDL_GetTicks() - m_startTicks;

		//Prevents frame finishing earlier and FPS breaking max fps
		if (desiredFrameTicks > frameTicks)
		{
			SDL_Delay(desiredFrameTicks - frameTicks);
		}

		if (track) trackFPS();

		m_startTicks = SDL_GetTicks();
	}

	//Announces FPS every NUM_SAMPLES frames
	void FPSManager::trackFPS()
	{
		static const int NUM_SAMPLES = 10;
		static Uint32 ticksPerFrame[NUM_SAMPLES];
		static int frameCount = 0;


		static Uint32 currentTicks;
		static Uint32 prevTicks = SDL_GetTicks();

		float ticksPerFrameTotal;
		float ticksPerFrameAverage;
		float m_FPSTracked;

		//Grabs number of ticks(ms) passed
		currentTicks = SDL_GetTicks();

		//Stores up to 10 samples of milliseconds passed since the previous frame
		ticksPerFrame[frameCount % NUM_SAMPLES] = currentTicks - prevTicks;

		//Stores current milliseconds passed, for next fps calculation
		prevTicks = currentTicks;
        
		frameCount++;
		
		//Resets the average frame time
		ticksPerFrameTotal = 0;

		//Calculates new average frame time
		for (int i = 0; i < std::min(frameCount, NUM_SAMPLES); i++)
		{
			ticksPerFrameTotal += ticksPerFrame[i];
		}

		ticksPerFrameAverage = ticksPerFrameTotal/std::min(frameCount, NUM_SAMPLES);
		
		//Sets _fps based on average frame time
		if (ticksPerFrameAverage > 0.0f)
		{
			m_FPSTracked = 1000.0f / ticksPerFrameAverage;
		}
		else
		{
			m_FPSTracked = 0.0f;
		}

		//Announces fps every 10 cycles
		if (frameCount%10 == 0)
		{
			std::cout << m_FPSTracked << std::endl;
		}
	}
}