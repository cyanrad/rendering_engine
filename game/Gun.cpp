#include "Gun.h"
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>

Gun::Gun(std::string name, int fireRate, float spread, int bulletsPerShot, int damage, float speed):
	_name(name),
	_fireRate(fireRate),
	_spread(spread),
	_bulletsPerShot(bulletsPerShot),
	_damage(damage),
	_speed(speed),
	_frameCounter(0)
{

}
Gun::~Gun()
{

}


void Gun::update(bool isMouseDown, const glm::vec2& direction, const glm::vec2& position, std::vector<Bullet>& bullets, float deltaTime)
{
	_frameCounter += 1.0f * deltaTime;
	if (_frameCounter >= _fireRate && isMouseDown)
	{
		fire(direction, position, bullets);
		_frameCounter = 0;
	}
}


void Gun::fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Bullet>& bullets)
{
	static std::mt19937 randomEngine(time(nullptr));
	std::uniform_real_distribution<float> randRotate(-_spread, _spread);

	for (int i = 0; i < _bulletsPerShot; i++){
		bullets.emplace_back(_damage,
			position, 
			glm::rotate(direction, randRotate(randomEngine)),
			_speed);
	}
}