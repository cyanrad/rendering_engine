#include "Level.h"

Level::Level(const std::string& fileName)
{
	//creating and opening the file
	std::ifstream file;
	file.open(fileName);

	if (file.fail()) { wangine::fetalError("failed to open level file: " + fileName); }	//<error checking>

	
	std::string tmp; //reading the first line

	file >> tmp >> _numHumans;	//we throw away the first string and read the int into _numhumans

	std::getline(file, tmp);//throw away empty first line
	//reads the rest of the txt file
	//and pushes it back into the vector
	while (std::getline(file, tmp))
	{
		_levelData.push_back(tmp);
	}

	_spriteBatch.init();
	_spriteBatch.begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	//color of the blocks
	wangine::Color whiteColor;
	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 255;

	//we need to loop through the whole level
	//looping through lines
	for (int y = 0; y < _levelData.size(); y++)
	{
		//looping through tiles
		for (int x = 0; x < _levelData[y].size(); x++)
		{
			//grabbing the tile
			char tile = _levelData[y][x];

			//get dest rect
			glm::vec4 destRect(x*TILE_WIDTH, y* TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			//processing the tile
			//switch statement to parce through the tiles and decide texture
			switch (tile)
			{
			//empty
			case '.':
				break;

			//red brick
			case 'R':
				_spriteBatch.draw(destRect,
									uvRect, 
									wangine::ResourceManager::getTexture("Textures/red_bricks.png").id, 0.0f, 
									whiteColor);
				break;

				//red brick
			case 'B':
				_spriteBatch.draw(destRect,
					uvRect,
					wangine::ResourceManager::getTexture("Textures/mc_bricks.png").id, 0.0f,
					whiteColor);
				break;

			//glass
			case 'G':
				_spriteBatch.draw(destRect,
					uvRect,
					wangine::ResourceManager::getTexture("Textures/glass.png").id, 0.0f,
					whiteColor);
				break;

			//light brick
			case 'L':
				_spriteBatch.draw(destRect,
					uvRect,
					wangine::ResourceManager::getTexture("Textures/light_bricks.png").id, 0.0f,
					whiteColor);
				break;
			
			//player
			case '@':
				_levelData[y][x] = '.';//so we dont collide
				_startPlayerPos.x = x * TILE_WIDTH;
				_startPlayerPos.y = y * TILE_WIDTH;
				break;

			//zombie
			case'Z':
				_levelData[y][x] = '.';//so we dont collide
				_startZombiePos.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
				break;

			//error
			default:
				std::printf("unexpected symbol %c at (%d, %d)", tile, x, y);
				break;
			}
		}
	}

	_spriteBatch.end();

}


void Level::draw()
{
	_spriteBatch.renderBatch();
}