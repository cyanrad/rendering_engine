#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Vertex.h"

namespace wangine {

//Glyph
//-----------------------------------------------------------------------------------------------------------------------------------
	//page(53)
	//is the sorting type of the glyphs
	enum class GlyphSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	//page(53)
	//a single class(holds sprite, texture, depth)
	class Glyph
	{
	public:
		//creating a constructor as to not make copies of the below variables, to be faster
		Glyph();
		Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color) :
			texture(Texture), depth(Depth)
		{
			//gives every edge of the rectangle a position and color
			topLeft.color = color;
			topLeft.setPosition(destRect.x, destRect.y + destRect.w);
			topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

			bottomLeft.color = color;
			bottomLeft.setPosition(destRect.x, destRect.y);
			bottomLeft.setUV(uvRect.x, uvRect.y);

			bottomRight.color = color;
			bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
			bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

			topRight.color = color;
			topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
			topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
		}
		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex topRight;
		Vertex bottomLeft;
		Vertex bottomRight;

	};

//Render Batch
//-----------------------------------------------------------------------------------------------------------------------------------
	//page(53, 59)
	//because we need to render batches before we draw them, and because we might have more than one batch
	class RenderBatch
	{
	public:
		RenderBatch(GLuint offset, GLuint numVertices, GLuint texture):
		offset(offset),
		numVertices(numVertices),
		texture(texture)
		{}

		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

//Sprite Bacth
//-----------------------------------------------------------------------------------------------------------------------------------
	class SpriteBatch
	{
	//page(56)
	public:
		SpriteBatch();

		void init();

		//page(58)
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();

		//page(56)
		//destination rectangle, UV rectangle
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);

		void renderBatch();

	//page(55)
	private:
		void createRenderBatches();
		//page(57)
		void createVertexArray();
		//page(58)
		void sortGlyphs();

		//page(59)
		static bool compareFrontToBack(Glyph* a, Glyph* b) { return a->depth < b->depth; }
		static bool compareBackToFront(Glyph* a, Glyph* b) { return a->depth > b->depth; }
		static bool compareTexture(Glyph* a, Glyph* b) { return a->texture < b->texture; }


		GLuint _vbo;
		GLuint _vao;

		GlyphSortType _sortType;

		std::vector<Glyph*> _glyphPointers;//this is for sorting
		std::vector<Glyph> _glyphs;//acutal glyphs 
		std::vector<RenderBatch> _renderBatches;
	};
}
