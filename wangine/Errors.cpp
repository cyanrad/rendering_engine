#include "Errors.h"
#include <iostream>
#include <SDL/SDL.h>

namespace wangine {
	void fetalError(std::string errorString)
	{
		std::cout << errorString << std::endl;
		std::cout << "Enter any key to quit...";
		std::cin.get();
		SDL_Quit();
		exit(69);
	}
}