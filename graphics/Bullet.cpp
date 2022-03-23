#include "Bullet.h"
#include <wangine/ResourceManager.h>


Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime)
{
	_lifeTime = lifeTime;
	_position = pos;
	_dircetion = dir;
	_speed = speed;
}


void Bullet::draw(wangine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static wangine::GLTexture texture = wangine::ResourceManager::getTexture("Textures/jimmyJump pack/PNG/CharacterLeft_Walk1.png");
	wangine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 30, 30);

	spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, color);
}

bool Bullet::update()
{
	_position += _dircetion * _speed;
	_lifeTime--;
	if (_lifeTime == 0) return 1;
	return 0;
}
