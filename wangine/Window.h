#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
#include <iostream>
#include "Errors.h"

namespace wangine {
	enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Window
	{
	public:
		int create(std::string windowName, int _screenWidth, int _screenHight, unsigned int currentFlag);
		void swapBuffer();
		int getScreenWidth() { return _screenWidth; }
		int getScreenhight() { return screenHight; }

	private:
		SDL_Window* _sdlWindow;
		int _screenWidth, screenHight;
	};
}