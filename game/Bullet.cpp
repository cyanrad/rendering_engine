#include "Bullet.h"
#include <wangine/ResourceManager.h>

Bullet::Bullet(int damage, glm::vec2 position, glm::vec2 direction, float speed):
	_damage(damage),
	_position(position),
	_direction(direction),
	_speed(speed)
{

}
Bullet::~Bullet()
{

}

void Bullet::update(float deltaTime,
	std::vector<Human*>& human,
	std::vector<Zombie*>& zombie)
{
	_position += _direction * _speed * deltaTime;
}

void Bullet::draw(wangine::SpriteBatch* spriteBatch)
{
	glm::vec4 destRect(
		_position.x + BULLET_RADIUS,
		_position.y + BULLET_RADIUS,
		BULLET_RADIUS * 2,
		BULLET_RADIUS * 2);
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	wangine::Color color; color.setColor(128, 128, 128, 255);

	spriteBatch->draw(destRect, uvRect, wangine::ResourceManager::getTexture("Textures/circle.png").id, 0.0f, color);
}