#pragma once
#include "GLTexture.h"
#include <string>

namespace wangine {
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);

	};
}

