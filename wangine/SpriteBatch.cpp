#include "SpriteBatch.h"
#include <algorithm>

namespace wangine {
//
SpriteBatch::SpriteBatch() :
	_vbo(0),
	_vao(0)
{

}

void SpriteBatch::init()
{
	createVertexArray();
}

//page(58)
//setting up the state before the rendering
void SpriteBatch::begin(GlyphSortType sortType /*= GlyphSortType::TEXTURE*/)
{
	_sortType = sortType;
	//sets the sort type (defult is TEXTURE)

	_renderBatches.clear();
	//resets the renderBatch array

	_glyphs.clear();
	//clears the glyph 
}

//page(62)
void SpriteBatch::end()
{
	_glyphPointers.resize(_glyphs.size());
	//creating a glyph pointer array the size of the glyphs array to be able to sort faster
	for(int i = 0; i <_glyphs.size(); i++ ){
		_glyphPointers[i] = &_glyphs[i];
	}
	sortGlyphs();
	createRenderBatches();
}

//page(56)
//destination rectangle, UV rectangle
//creats a new glyph
void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color)
{
	//pushes back the newGlyph in the Glyphs buffer
	_glyphs.emplace_back(destRect, uvRect, texture, depth, color);
}

//page(62)
//loops through the renderBatches and draw them
void SpriteBatch::renderBatch()
{
	glBindVertexArray(_vao);

	for (int i = 0; i < _renderBatches.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

		glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
	}

	glBindVertexArray(0);
}

//page(60, 61)
void SpriteBatch::createRenderBatches()
{
	std::vector<Vertex> vertices;
	vertices.resize(_glyphs.size() * 6);

	if (_glyphs.empty()) { return; }

	int cv = 0; //durrent vertex
	int offset = 0;
	_renderBatches.emplace_back(offset, 6, _glyphPointers[0]->texture);
	vertices[cv++] = _glyphPointers[0]->topLeft;
	vertices[cv++] = _glyphPointers[0]->bottomLeft;
	vertices[cv++] = _glyphPointers[0]->bottomRight;
	vertices[cv++] = _glyphPointers[0]->bottomRight;
	vertices[cv++] = _glyphPointers[0]->topRight;
	vertices[cv++] = _glyphPointers[0]->topLeft;

	//page(61)
	for (int cg = 1; cg < _glyphPointers.size(); cg++)
	{
		if (_glyphPointers[cg]->texture != _glyphPointers[cg - 1]->texture) {
			_renderBatches.emplace_back(offset, 6, _glyphPointers[cg]->texture);
		}
		else {
			_renderBatches.back().numVertices += 6;
		}

		vertices[cv++] = _glyphPointers[cg]->topLeft;
		vertices[cv++] = _glyphPointers[cg]->bottomLeft;
		vertices[cv++] = _glyphPointers[cg]->bottomRight;
		vertices[cv++] = _glyphPointers[cg]->bottomRight;
		vertices[cv++] = _glyphPointers[cg]->topRight;
		vertices[cv++] = _glyphPointers[cg]->topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	//orphan the buffer
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), /*vertices.data()*/nullptr, GL_DYNAMIC_DRAW);
	//upload the data
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//page(57)
void SpriteBatch::createVertexArray()
{
	if (_vao == 0) { glGenVertexArrays(1, &_vao); }
	glBindVertexArray(_vao);
	//binds the vertex array object

	if (_vbo == 0) { glGenBuffers(1, &_vbo); }
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	//binds the buffer, if the vao gets rebinded it will rebind the buffer aswell 

	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//enables the attributeArray in (GLSL)

	//this is the position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	//color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	//UV attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindVertexArray(0);
	//unbinds the vertex array
}

//page(58)
//this will determin the sorting type for glyphs
void SpriteBatch::sortGlyphs()
{
	//we are sorting with the glyphPointers because it's faster
	switch (_sortType)
	{
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareBackToFront);
		break;
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareFrontToBack);
		break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareTexture);
		break;
	}
}
//
}