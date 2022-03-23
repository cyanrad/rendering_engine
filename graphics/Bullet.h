#pragma once
#include <glm/glm.hpp>
#include <wangine/SpriteBatch.h>

class Bullet
{
public:
	Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime);
	void draw(wangine::SpriteBatch& spriteBatch);
	//returns true when no lifetime
	bool update();


private:
	int _lifeTime;
	float _speed;
	glm::vec2 _dircetion;
	glm::vec2 _position;
};

