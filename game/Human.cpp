#include "Human.h"

Human::Human():
	_frames(0)
{

}
Human::~Human()
{

}

void Human::init(float speed, glm::vec2 pos)
{
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> randDir(-1.0f, 1.0f);

	_color.setColor(255, 255, 255, 255);

	_speed = speed;
	_position = pos;

	_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));

	//makes sure direction != 0
	if (_direction.length() == 0) _direction = glm::vec2(1.0f, 0.0f);

	//normalize
	_direction = glm::normalize(_direction);
}

void Human::update(float deltaTime,
	std::vector<std::string>& levelData,
	std::vector<Human*>& human,
	std::vector<Zombie*>& zombie)
{
	_position += _direction * _speed * deltaTime;

	//randomly change direction every 20 frames
	if (_frames == 100 || CollideWithLevel(levelData)) {
			static std::mt19937 randomEngine(time(nullptr));
			static std::uniform_real_distribution<float> randRotate(-20.0f, 20.0f);

			_direction = glm::rotate(_direction, randRotate(randomEngine));
			_frames = 0;
	}
	else { _frames++; }

	CollideWithLevel(levelData);
}