#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <wangine/Errors.h>
#include <iostream>
#include <wangine/SpriteBatch.h>
#include <wangine/ResourceManager.h>

const int TILE_WIDTH = 64;

class Level
{
public:
	//the constructor will build the level
	Level(const std::string& fileName);

	//draws the level
	void draw();

	//getters
	int getLevelWidth() const { return _levelData[0].size(); }
	int getLevelHight() const { return _levelData.size(); }
	std::vector<std::string>& getLevelData() { return _levelData; }
	glm::vec2 getStartPlayerPos() const { return _startPlayerPos; }
	const std::vector<glm::vec2>& getStartZombiePos() const { return _startZombiePos; }
	int getNumHumans() const { return _numHumans; }

private:
	//this is a vector of strings that’s going to store the level data
	std::vector<std::string> _levelData;
	//number of humans in the map
	int _numHumans;

	wangine::SpriteBatch _spriteBatch;
	wangine::ResourceManager* _resourceManager; //<this is a pointer to manager to main game>

	glm::vec2 _startPlayerPos;
	std::vector<glm::vec2> _startZombiePos;
};

