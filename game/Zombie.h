#pragma once
#include "Agent.h"
#include "Human.h"

class Zombie : public Agent
{

public:
	void init(float speed, glm::vec2 position);

	virtual void update(float deltaTime,
		std::vector<std::string>& levelData,
		std::vector<Human*>& human,
		std::vector<Zombie*>& zombie)override;

private:
	Human* getNearestHuman(std::vector<Human*>& human);
};

