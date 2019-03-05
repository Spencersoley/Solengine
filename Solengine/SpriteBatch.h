#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Vertex.h"

namespace Solengine
{
	enum class GlyphSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	class Glyph
	{
	public:
		Glyph() {};
		Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint txtr, float dpth, const ColourRGBA8& clr) : texture(txtr), depth(dpth) //note: initialiser lists are slightly faster than manually assigning
		{
			topLeft.colour = clr;
			topLeft.setPosition(destRect.x, destRect.y + destRect.w);
			topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

			bottomLeft.colour = clr;
			bottomLeft.setPosition(destRect.x, destRect.y);
			bottomLeft.setUV(uvRect.x, uvRect.y);

			bottomRight.colour = clr;
			bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
			bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

			topRight.colour = clr;
			topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
			topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
		}

		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	};

	class RenderBatch 
	{
	public:
		RenderBatch(GLuint offst, GLuint numVerts, GLuint txtr) :
			offset(offst),
			numVertices(numVerts), 
			texture(txtr)
		{

		}

		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void init();
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour);
		void renderBatch();

	private:
		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);
		
		GLuint _vbo;
		GLuint _vao;

		GlyphSortType _sortType;

		std::vector<Glyph*> _pGlyphs; // for sorting
		std::vector<Glyph> _glyphs; // actual glyphs
		std::vector<RenderBatch> _renderBatches;

	};
}