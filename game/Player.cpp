#include "Player.h"
#include "Gun.h"


Player::Player(): _currentGunIndex(-1){}
Player::~Player()
{

}

void Player::init(float speed, glm::vec2 position, wangine::InputManager* inputManager, wangine::Camera2D* camera, std::vector<Bullet>* bullet)
{
	_speed = speed;
	_position = position;
	_inputManager = inputManager;
	_color.setColor(255.0f,255.0f, 255.0f, 255.0);
	_camera = camera;
	_bullet = bullet;
}

void Player::addGun(Gun* gun) {
	_guns.push_back(gun);

	//if no guns equibed, equib gun
	if (_currentGunIndex == -1)
		_currentGunIndex = 0;
}

//error maybe
void Player::update(float deltaTime,
	std::vector<std::string>& levelData,
	std::vector<Human*>& human,
	std::vector<Zombie*>& zombie)
{
	if (_inputManager->isKeyPressed(SDLK_w)){
		_position.y += _speed * deltaTime;
	}else if(_inputManager->isKeyPressed(SDLK_s)){
		_position.y -= _speed * deltaTime;
	}

	if (_inputManager->isKeyPressed(SDLK_a)) {
		_position.x -= _speed * deltaTime;
	}
	else if (_inputManager->isKeyPressed(SDLK_d)) {
		_position.x += _speed * deltaTime;
	}

	if (_inputManager->isKeyPressed(SDLK_1) && _guns.size() >= 0)
	{
		_currentGunIndex = 0;
	}
	else if (_inputManager->isKeyPressed(SDLK_2) && _guns.size() >= 1)
	{
		_currentGunIndex = 1;
	}


	glm::vec2 mouseCoords = _camera->ConvertScreen2World(_inputManager->getMouseCoords());
	glm::vec2 centerPos = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 direction = glm::normalize(mouseCoords - centerPos);

	if (_currentGunIndex != -1) {
		_guns[_currentGunIndex]->update(
			_inputManager->isKeyPressedTrue(SDL_BUTTON_LEFT),
			centerPos,
			direction,
			*_bullet,
			deltaTime);
	}

	CollideWithLevel(levelData);
}


//pos getter
glm::vec2 Player::getPlayerPos() { return _position; }