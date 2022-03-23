#pragma once
#include <algorithm>
#include <glm/glm.hpp>
#include <wangine/SpriteBatch.h>
#include <wangine/ResourceManager.h>
#include "Level.h"


const float AGENT_WIDTH = 60;

class Zombie;
class Human;


class Agent
{
public:
	Agent();
	virtual ~Agent();

	virtual void update(float deltaTime,
		std::vector<std::string>& levelData,
						std::vector<Human*>& human,
						std::vector<Zombie*>& zombie) = 0;

	bool CollideWithLevel(std::vector<std::string>& levelData);

	void draw(wangine::SpriteBatch* spriteBatch);

	bool collideWithAgent(Agent* agent);

	glm::vec2 getPosition() { return _position; }

protected:
	void checkTilePos(std::vector<std::string>& levelData, 
					std::vector<glm::vec2>& collideTilePos,
					float x, float y);

	void collideWithTile(glm::vec2 tilePos);

	const float AGENT_RADIUS = (float)AGENT_WIDTH / 2;
	glm::vec2 _position;
	wangine::Color _color;
	float _speed;
};

