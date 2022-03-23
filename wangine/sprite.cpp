#include "sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"
#include <cstddef>
#include <iostream>

namespace wangine {
	sprite::sprite()
	{
		_vboID = 0;
	}
	sprite::~sprite()
	{
		if (_vboID != 0) {
			glDeleteBuffers(1, &_vboID);
		}
	}

	void sprite::init(float x, float y, float width, float hight, std::string texturePath)
	{

		_x = x;
		_y = y;
		_width = width;
		_hight = hight;

		_texture = ResourceManager::getTexture(texturePath);



		if (_vboID == 0)
		{
			glGenBuffers(1, &_vboID);
		}

		Vertex vertexData[12];
		//thsi is for the rectangle shape
		//first triangle
		vertexData[0].setPosition(x + width, y + hight);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPosition(x, y + hight);
		vertexData[1].setUV(0.0f, 1.0f);

		vertexData[2].setPosition(x, y);
		vertexData[2].setUV(0.0f, 0.0f);

		//second triangle
		vertexData[3].setPosition(x, y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPosition(x + width, y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPosition(x + width, y + hight);
		vertexData[5].setUV(1.0f, 1.0f);


		//color loop
		//comment to disable color
		//for (int i = 0; i < 12; i++)
		//{
		//	vertexData[i].setColor(0, 0, 0, 0);
		//}

		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void sprite::draw()
	{
		glBindTexture(GL_TEXTURE_2D, _texture.id);

		glBindBuffer(GL_ARRAY_BUFFER, _vboID);


		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}