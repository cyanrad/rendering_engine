#include <SDL/SDL.h>
#include <GL/glew.h>

namespace wangine {
	int init()
	{
		//init SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		//sets the window mode to doubleBuffer (reloads twice for better frames)
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}
}