#include "Window.h"
namespace wangine {
	int Window::create(std::string windowName, int _screenWidth, int _screenHight, unsigned int currentFlag)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlag & INVISIBLE)
			flags |= SDL_WINDOW_HIDDEN;
		if (currentFlag & FULLSCREEN)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		if (currentFlag & BORDERLESS)
			flags |= SDL_WINDOW_BORDERLESS;


		//creats a widnow + error checking
		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHight, flags);
		if (_sdlWindow == nullptr) { fetalError("SDL window could not be created"); }

		//combination of SDL and GL + error checking
		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (glContext == nullptr) { fetalError("SDL_GL context could not be created"); }

		//initialises glew + error checking
		GLenum error = glewInit();
		if (error != GLEW_OK) { fetalError("could not init glew"); }

		//sets the color of the window
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		//print out openGL version
		//GL_VERION is a pointer to the string which contains the version
		std::cout << glGetString(GL_VERSION);

		//tun on Vsync
		SDL_GL_SetSwapInterval(0);

		//enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}


	void Window::swapBuffer()
	{
		SDL_GL_SwapWindow(_sdlWindow);
	}
}