#include "MainGame.h"
#include <wangine/Errors.h>
#include <wangine/Timing.h>
#include <wangine/ResourceManager.h>
#include <glm/glm.hpp>

#include <iostream>
#define print std::cout <<

MainGame::MainGame() :  
	_screenWidth(1024), 
	_screenHight(768), 
	_time(0.0f),
	_gameState(GameState::PLAY),
	_maxFPS(60.0)
{ 
	_camera.init(_screenWidth, _screenHight);
}
MainGame::~MainGame() {}


void MainGame::run()
{
	//initialization of libraries and window
	initSystems();
	
	//starts the game loop
	gameLoop();

}

void MainGame::initSystems()
{
	//initializes the winodw
	wangine::init();

	//creats window
	_window.create("Game Window", _screenWidth, _screenHight, 0);

	//initialize shader
	initShaders();

	_spriteBatch.init();

	_fpsLimiter.init(_maxFPS);
}

void MainGame::initShaders()
{
	//compile the shaders
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");

	//creats attributes so they can be used in the texture shader
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");

	//links the shaders
	_colorProgram.linkShaders();

}

void MainGame::gameLoop() 
{
	//the main game loop that draws stuff
	while (_gameState != GameState::EXIT)
	{
		//begin the fps timer
		_fpsLimiter.begin();

		processInput();

		//increases tome
		_time += 0.1;

		//updates the camera
		_camera.update();

		//updates bullets
		for (int i = 0; i < _bullets.size();)
		{
			if (_bullets[i].update() == true)
			{
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}
			else i++;
		}

		//draws on the window
		drawGame();

		//ends the fps timer
		_FPS = _fpsLimiter.end();

		//outputs every 10 frames
		//avrages frames for output
		//static int frameCount = 0;
		//frameCount++;
		//if (frameCount == 10)
		//{
		//	print int(_FPS) << std::endl;
		//	frameCount = 0;
		//}
	}
};

void MainGame::processInput()
{
	int CAMERASPEED = 30;
	const float SCROLLSPEED = 0.1f;
	//gets input events
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) 
	{
		switch (evnt.type)
		{
		//keyboard
		case SDL_QUIT:
			_gameState = GameState::EXIT;
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
		case SDL_MOUSEBUTTONUP :
			_inputManager.releaseKey(evnt.button.button);
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		}
	}

	//input processing
	if (_inputManager.isKeyPressed(SDLK_w))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, CAMERASPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_s))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -CAMERASPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_a))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERASPEED, .0));
	}
	if (_inputManager.isKeyPressed(SDLK_d))
	{
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERASPEED, 0));
	}
	if (_inputManager.isKeyPressed(SDLK_e))
	{
		_camera.setScale(_camera.getScale() + SCROLLSPEED);
	}
	if (_inputManager.isKeyPressed(SDLK_q))
	{
		_camera.setScale(_camera.getScale() + -SCROLLSPEED);
	}
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT))
	{
		//glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		glm::vec2 mouseCoords = _camera.ConvertScreen2World(_inputManager.getMouseCoords());
		//std::cout << mouseCoords.x << " " << mouseCoords.y << std::endl;

		glm::vec2 playerPosition(0.0f);
		glm::vec2 direction = mouseCoords - playerPosition;
		direction = glm::normalize(direction);

		//creates the bullets
		_bullets.emplace_back(mouseCoords, direction, 10.0f, 10);
	}

};

void MainGame::drawGame()
{

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();

	glActiveTexture(GL_TEXTURE0);


	//unioform uploading
	GLint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1f(textureLocation, 0);

	//GLint timeLocation = _colorProgram.getUniformLocation("time");
	//glUniform1f(timeLocation, _time);

	_spriteBatch.begin();

	glm::vec4 position(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static wangine::GLTexture texture = wangine::ResourceManager::getTexture("Textures/jimmyJump pack/PNG/CharacterLeft_Walk1.png");
	wangine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	
	_spriteBatch.draw(position, uv, texture.id, 0.0f, color);

	//drawing bullets
	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].draw(_spriteBatch);
	}

	_spriteBatch.end();

	_spriteBatch.renderBatch();


	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();
	_window.swapBuffer();

}
