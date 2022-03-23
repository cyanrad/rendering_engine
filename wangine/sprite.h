#pragma once
#include <GL/glew.h>
#include <string>
#include "GLTexture.h"

namespace wangine {
	class sprite
	{
	public:
		sprite();
		~sprite();

		void init(float x, float y, float width, float hight, std::string texturePath);
		void draw();


	private:
		int _x;
		int _y;
		int _width;
		int _hight;
		GLuint _vboID;
		GLTexture _texture;
	};
}
