#pragma once

#include <GL/glew.h>

namespace wangine {
	struct Position
	{
		float x, y;
	};

	struct Color
	{
		GLubyte r, g, b, a;
		void setColor(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a)
		{
			r = _r;
			g = _g;
			b = _b;
			a = _a;
		}
	};

	struct UV
	{
		float u, v;
	};

	//vertex properties
	struct Vertex
	{
		//this is called compostition
		Position position;
		Color color;
		UV uv;

		void setPosition(float x, float y)
		{
			position.x = x;
			position.y = y;
		}

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void setUV(float u, float v)
		{
			uv.u = u;
			uv.v = v;
		}
	};
}