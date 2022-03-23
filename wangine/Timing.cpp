#include "Timing.h"

namespace wangine {

	FPSLimiter::FPSLimiter() {

	}

	void FPSLimiter::init(float maxFPS)
	{
		setMaxFPS(maxFPS);
	}

	void FPSLimiter::begin()
	{
		_startTicks = SDL_GetTicks();
	}

	//returns current FPS
	float FPSLimiter::end()
	{
		calculateFPS();

		float frameTicks = SDL_GetTicks() - _startTicks;

		if (1000.0f / _maxFPS > frameTicks)
			SDL_Delay(1000.0f / _maxFPS - frameTicks);

		return _FPS;
	}

	void FPSLimiter::calculateFPS()
	{
		static const int NUM_SAMPLES = 10;
		static float frameTimes[NUM_SAMPLES];
		static int currentFrame = 0;

		static float prevTicks = SDL_GetTicks();
		float currentTicks = SDL_GetTicks();

		_frameTime = currentTicks - prevTicks;
		frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;
		currentFrame++;

		prevTicks = currentTicks;

		int count;
		if (currentFrame < NUM_SAMPLES)
			count = currentFrame;
		else
			count = NUM_SAMPLES;

		float frameTimeAvrage = 0;
		for (int i = 0; i < count; i++)
			frameTimeAvrage += frameTimes[i];

		frameTimeAvrage /= count;

		if (frameTimeAvrage > 0)
			_FPS = 1000.f / frameTimeAvrage;
		else
			_FPS = 60.0f;

	}

}