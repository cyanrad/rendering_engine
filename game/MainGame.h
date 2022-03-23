#pragma once
#include <wangine/Window.h>
#include <wangine/wangine.h>
#include <wangine/GLSLProgram.h>
#include <wangine/Camera2D.h>
#include <wangine/InputManager.h>
#include <wangine/Timing.h>
#include <wangine/SpriteBatch.h>
#include <SDL/SDL.h>
#include "Player.h"
#include "Level.h"
#include "Zombie.h"
#include "Gun.h"
#include "Bullet.h"

enum class GameState
{
	PLAY,
	EXIT
};

class Zombie;

class MainGame
{
public:
	MainGame();
	~MainGame();
	void run();

private:
	//initializes the system
	void initSystems();

	//init shaders
	void initShaders();

	//inits levels and setsup everything
	void initLevel();

	//main game loop
	void gameLoop();

	//handels input
	void processInput();

	//draws game
	void drawGame();

	//updates agents
	void updateAgents(float deltaTime);

	//update bullets
	void updateBullets(float deltaTime);

	//wangine member variables
	wangine::Window _window;
	wangine::GLSLProgram _textureProgram;
	wangine::InputManager _inputManager;
	wangine::Camera2D _camera;
	wangine::SpriteBatch _agentSpriteBatch;//draws agents
	std::vector<Level*> _levels;

	int _screenW;
	int _screenH;
	float _fps;
	int _currentLevel;
	Player* _player;
	std::vector<Human*> _human; //vec of all humans
	std::vector<Zombie*> _zombie; //vec of all zombie
	std::vector<Bullet> _bullet;
	GameState _gameState;
};

