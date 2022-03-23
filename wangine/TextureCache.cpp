#include "TextureCache.h"
#include "ImageLoader.h"

namespace wangine {
	GLTexture TextureCache::getTexture(std::string texturePath)
	{
		//std::map<std::string, GLTexture>::iterator
		//lookup the texture and see if it's inathe map
		auto mit = _textureMap.find(texturePath);

		//check if it's not in the map
		if (mit == _textureMap.end())
		{
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);
			//insert int map
			_textureMap[texturePath] = newTexture;

			return newTexture;
		}

		return mit->second;
	}
}