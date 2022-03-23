#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <wangine/SpriteBatch.h>

const int BULLET_RADIUS = 5;
class Human;
class Zombie;
class Bullet
{
public:
	Bullet(int damage, glm::vec2 position, glm::vec2 direction, float speed);
	~Bullet();

	void update(float deltaTime,
				std::vector<Human*>& human,
				std::vector<Zombie*>& zombie);

	void draw(wangine::SpriteBatch *spriteBatch);

private:
	glm::vec2 _position;
	glm::vec2 _direction;
	float _speed;
	int _damage;
};

