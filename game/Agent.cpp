#include "Agent.h"


Agent::Agent()
{

}
Agent::~Agent()
{

}


void Agent::draw(wangine::SpriteBatch* spriteBatch)
{
	static int textureID = wangine::ResourceManager::getTexture("Textures/player.png").id;

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;

	spriteBatch->draw(destRect, uvRect, textureID, 1, _color);
}

void Agent::update(float deltaTime,
	std::vector<std::string>& levelData,
	std::vector<Human*>& human,
	std::vector<Zombie*>& zombie){}

bool Agent::CollideWithLevel(std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collideTilePos;

	//check the four cornres
	//first corner
	checkTilePos(levelData, collideTilePos, _position.x, _position.y);

	//second corner
	checkTilePos(levelData, collideTilePos, _position.x + AGENT_WIDTH, _position.y);

	//third corner
	checkTilePos(levelData, collideTilePos, _position.x, _position.y + AGENT_WIDTH);

	//forth corner
	checkTilePos(levelData, collideTilePos, _position.x + AGENT_WIDTH, _position.y + AGENT_WIDTH);

	if (collideTilePos.size() == 0)
	{
		return false;
	}

	//does collision
	for (int i = 0; i < collideTilePos.size(); i++)
	{
		collideWithTile(collideTilePos[i]);
	}

	return true;
}


void Agent::checkTilePos(std::vector<std::string>& levelData,
						std::vector<glm::vec2>& collideTilePos,
						float x, float y)
{
	glm::vec2 cornerPos = glm::vec2(floor(x / (float)TILE_WIDTH),
									floor(y / (float)TILE_WIDTH)) ;

	//if agent is outside the world return
	if(cornerPos.x < 0 || cornerPos.x >= levelData[0].size() ||
		cornerPos.y < 0 || cornerPos.y >= levelData.size()) {
		return;
	}

	if (levelData[cornerPos.y][cornerPos.x] != '.')
	{
		collideTilePos.push_back((float)TILE_WIDTH * cornerPos + glm::vec2((float)TILE_WIDTH/2.0f));
	}
}


//axis alligned bb collision
void Agent::collideWithTile(glm::vec2 tilePos)
{

	const float TILE_RADIUS = (float)TILE_WIDTH / 2;
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

	glm::vec2 centerPlayerPos = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = centerPlayerPos - tilePos;
	
	float xDepth = MIN_DISTANCE - abs(distVec.x);
	float yDepth = MIN_DISTANCE - abs(distVec.y);


	//if true then we are colliding
	if (xDepth > 0 || yDepth > 0)
	{
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f))
		{
			if (distVec.x < 0) {
				_position.x -= xDepth;
			}else {
				_position.x += xDepth;}

		} else{
			if (distVec.y < 0) {
				_position.y -= yDepth;
			}else{
				_position.y += yDepth;
			}

		}
	}
}

//check cullsion useing sphire collision
bool Agent::collideWithAgent(Agent* agent)
{
	glm::vec2 centerPosA = _position + glm::vec2 (AGENT_RADIUS);
	glm::vec2 centerPosB = agent -> getPosition() + glm::vec2(AGENT_RADIUS);

	const float MIN_DISTANCE = AGENT_RADIUS * 2;

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - distance;
	if (collisionDepth > 0)
	{
		glm::vec2 collsionDepthVec = glm::normalize(distVec) * collisionDepth;

		_position += collsionDepthVec / 2.0f;
		agent->_position -= collsionDepthVec / 2.0f;
		return true;
	}
	return false;
}

