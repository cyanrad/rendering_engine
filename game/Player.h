#pragma once
#include "Human.h"
#include "Bullet.h"
#include <wangine/InputManager.h>
#include <SDL/SDL.h>
#include <wangine/Camera2D.h>

class Gun;
class Player : public Human
{
public:
	Player();
	virtual ~Player();

	void init(float speed, glm::vec2 position, wangine::InputManager* inputManager, wangine::Camera2D* camera, std::vector<Bullet>* bullet);

	void update(float deltaTime,
		std::vector<std::string>& levelData,
		std::vector<Human*>& human,
		std::vector<Zombie*>& zombie)override;

	void addGun(Gun* gun);

	glm::vec2 getPlayerPos();

private:
	wangine::InputManager* _inputManager;
	std::vector<Gun*> _guns;
	wangine::Camera2D* _camera;
	int _currentGunIndex;
	std::vector<Bullet>* _bullet;
};

