#include <Windows.h>
#include <iostream>

#include <GL/glew.h>
#include "MainGame.h"

int main(int argc, char** argv) 
{
	MainGame maingame;
	maingame.run();

	return 0;
}