#pragma once
#include <map>
#include <string>
#include "GLTexture.h"

namespace wangine {
	class TextureCache
	{
	public:
		GLTexture getTexture(std::string texturePath);

	private:
		std::map<std::string, GLTexture> _textureMap;
	};
}
