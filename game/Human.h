#pragma once
#include "Agent.h"
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>

class Human : public Agent
{

public:
	Human();
	virtual ~Human();
	void init(float speed, glm::vec2 pos);
	virtual void update(
		float deltaTime,
		std::vector<std::string>& levelData,
		std::vector<Human*>& human,
		std::vector<Zombie*>& zombie) override;

private:
	glm::vec2 _direction;
	float _trueSpeed;
	int _frames;

};

