#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>
#include "Bullet.h"

#include <wangine/wangine.h>
#include <wangine/GLSLProgram.h>
#include <wangine/GLTexture.h>
#include <wangine/Window.h>
#include <wangine/Camera2d.h>
#include <wangine/SpriteBatch.h>
#include <wangine/InputManager.h>
#include <wangine/Timing.h>

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();
	
private:
	//functions
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();

	//window
	wangine::Window _window;
	int _screenWidth;
	int _screenHight;

	//gamestate
	GameState _gameState;

	//shaders
	wangine::GLSLProgram _colorProgram;
	wangine::Camera2D _camera;
	wangine::SpriteBatch _spriteBatch;
	wangine::InputManager _inputManager;
	wangine::FPSLimiter _fpsLimiter;

	std::vector<Bullet> _bullets;

	//benchmarking
	float _time;
	float _FPS;
	float _maxFPS;
};

