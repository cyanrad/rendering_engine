#include "MainGame.h"


const float HUMAN_SPEED = 1.0f;
const float ZOMBIE_SPEED = 1.3f;

MainGame::MainGame():
_screenH(720),
_screenW(1080),
_gameState(GameState::PLAY),
_currentLevel(0),
_fps(0),
_player(nullptr)
{
	//empty
}
MainGame::~MainGame()
{
	delete _player;
	for (int i = 0; i < _levels.size(); i++)
	{
		delete _levels[i];
	}
	for (int i = 0; i < _zombie.size(); i++)
	{
		delete _zombie[i];
	}
	for (int i = 0; i < _human.size(); i++)
	{
		delete _human[i];
	}
}


//runs the game
void MainGame::run()
{
	initSystems();
	initLevel();

	gameLoop();
}

//initializes the system
void MainGame::initSystems()
{
	//init wangine
	wangine::init();

	//creating window
	_window.create("game", _screenW, _screenH, 0);
	glClearColor(0.6f,0.6f,0.6f,1.0f);

	//initializes shaders
	initShaders();

	_agentSpriteBatch.init();

	//init camera
	_camera.init(_screenW, _screenH);
}

//initialises the level
void MainGame::initLevel()
{
	//pushing back level 1
	_levels.push_back(new Level("Levels/level1.txt"));

	//initializing player
	_player = new Player();
	_player->init(10.0f, _levels[_currentLevel]->getStartPlayerPos(), &_inputManager, &_camera, &_bullet);

	_human.push_back(_player);

	//rand pos gen
	static std::mt19937 randomEngine;
	randomEngine.seed(time(nullptr));
	static std::uniform_int_distribution<int> randx(2, _levels[_currentLevel]->getLevelWidth() - 2);
	static std::uniform_int_distribution<int> randy(2, _levels[_currentLevel]->getLevelHight() - 2);
	


	//add all random humans
	for (int i = 0; i < _levels[_currentLevel]->getNumHumans(); i++)
	{
		_human.push_back(new Human);
		glm::vec2 pos(randx(randomEngine) * TILE_WIDTH, randy(randomEngine) * TILE_WIDTH);
		_human.back()->init(HUMAN_SPEED, pos);
	}

	//add all zombies
	const std::vector<glm::vec2>& zombiePosition = _levels[_currentLevel]->getStartZombiePos();
	for (int i = 0; i < zombiePosition.size(); i++)
	{
		_zombie.push_back(new Zombie);
		_zombie.back()->init(ZOMBIE_SPEED, zombiePosition[i]);
	}


	//setUp player Gun
	_player->addGun(new Gun("psitol", 30, 1, 10, 30, 20));
	_player->addGun(new Gun("shotGun", 60, 10, 40, 10, 20));
}


//update bullets
void MainGame::updateBullets(float deltaTime)
{
	for (int i = 0; i < _bullet.size(); i++) {
		_bullet[i].update(deltaTime,
			_human, _zombie);
	}
}

//updates agents
void MainGame::updateAgents(float deltaTime)
{
	//update All Humans
	for (int i = 0; i < _human.size(); i++)
	{
		_human[i]->update(deltaTime,
			_levels[_currentLevel]->getLevelData(),
						_human,
						_zombie);
	}

	//update all zombies
	for (int i = 0; i < _zombie.size(); i++)
	{
		_zombie[i]->update(deltaTime,
			_levels[_currentLevel]->getLevelData(),
			_human,
			_zombie);
	}


	//update human collisions
	for (int i = 0; i < _human.size(); i++)
	{
		for (int j = i + 1; j < _human.size(); j++)
		{
			_human[i]->collideWithAgent(_human[j]);
		}
	}

	//update zombies
	for (int i = 0; i < _zombie.size(); i++){
		//collision with zombies
		for (int j = 1; j < _zombie.size(); j++)
			_zombie[i]->collideWithAgent(_zombie[j]);

		//collision with human
		for (int j = 1; j < _human.size(); j++){
			if (_zombie[i]->collideWithAgent(_human[j])) {
				// Add the new zombie
				_zombie.push_back(new Zombie);
				_zombie.back()->init(ZOMBIE_SPEED, _human[j]->getPosition());
				//remove human
				delete _human[j];
				_human[j] = _human.back();
				_human.pop_back();
			}
		}
	}
}

//init shaders
void MainGame::initShaders()
{
	//compile the shaders
	_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");

	//creats attributes so they can be used in the texture shader
	_textureProgram.addAttribute("vertexPosition");
	_textureProgram.addAttribute("vertexColor");
	_textureProgram.addAttribute("vertexUV");

	//links the shaders
	_textureProgram.linkShaders();
}


//main game loop
void MainGame::gameLoop()
{
	wangine::FPSLimiter fpsLimiter;
	fpsLimiter.setMaxFPS(120);

	const float DESIRED_FPS = 60;
	const float MS_PER_SECOND = 1000;
	const float DESIRED_FRAMETIME = MS_PER_SECOND/ DESIRED_FPS;
	const float MAX_DELTA_TIME = 1.0f;
	const int MAX_STEPS = 6;
	float prevTicks = SDL_GetTicks();

	while (_gameState == GameState::PLAY)
	{
		fpsLimiter.begin();

		float newTicks = SDL_GetTicks();
		float frameTime = newTicks -prevTicks;
		prevTicks = newTicks;
		float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

		_inputManager.update();
		
		processInput();

		int i = 0;
		while (totalDeltaTime > 0.0f && i < MAX_STEPS)
		{
			float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
			updateAgents(deltaTime);
			updateBullets(deltaTime);
			totalDeltaTime -= deltaTime;
			i++;
		}


		_camera.setPosition(_player->getPlayerPos());
		_camera.update();

		drawGame();

		_fps = fpsLimiter.end();
	}
}

//handels input
void MainGame::processInput() 
{
	int CAMERASPEED = 30;
	const float SCROLLSPEED = 0.05f;

	//gets input events
	SDL_Event evnt;
	//loops until there is no more events
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
			//keyboard
		case SDL_QUIT:
			break;
		case SDL_KEYDOWN:
			_inputManager.PressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
			//mouse
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.PressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		}
	}
}


void MainGame::drawGame()
{
	//sets base depth to 1
	glClearDepth(1.0f);

	//clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_textureProgram.use();

	//drwaing goes here
	//activateing and setting the smapler texture
	//makes sure the shader uses texture 0
	glActiveTexture(GL_TEXTURE0);
	GLint textureUniform = _textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	//prjection matrix
	glm::mat4 projectionMatrix = _camera.getCameraMatrix();
	GLint pUniform = _textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	//draws the level
	_levels[_currentLevel]->draw();

	//begin drawing agentspritebatch
	_agentSpriteBatch.begin();


	//draws zombies
	for (int i = 0; i < _zombie.size(); i++)
	{
		_zombie[i]->draw(&_agentSpriteBatch);
	}
	
	//draws player/ humans
	for (int i = 0; i < _human.size(); i++)
	{
		_human[i]->draw(&_agentSpriteBatch);
	}

	//draw the bullets
	for (int i = 0; i < _bullet.size(); i++)
	{
		std::cout << _bullet.size();
		_bullet[i].draw(&_agentSpriteBatch);
	}

	_agentSpriteBatch.end();
	_agentSpriteBatch.renderBatch();

	_textureProgram.unuse();

	//swap our buffer and draws everything to the screen
	_window.swapBuffer();
}