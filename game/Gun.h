#pragma once
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include "Bullet.h"

class Gun
{
public:
	Gun(std::string name, int fireRate, float spread, int bulletsPerShot, int damage, float speed);
	~Gun();

	void update(bool isMouseDown, const glm::vec2& direction, const glm::vec2& position, std::vector<Bullet>& bullets, float deltaTime);
private:
	void fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Bullet>& bullets);

	std::string _name;
	int _fireRate;//fireRate interms of frames
	float _spread;//accuracy
	int _bulletsPerShot;
	int _damage;
	float _speed;
	float _frameCounter;
};

