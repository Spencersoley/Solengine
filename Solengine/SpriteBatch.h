#pragma once

#include "SpriteBase.h"

namespace Solengine
{
	class RenderBatch 
	{
	public:
		RenderBatch(GLuint offst, GLuint numVerts, GLuint txtr) :
			offset(offst),
			numVertices(numVerts), 
			texture(txtr)
		{}

		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

	class SpriteBatch : public SpriteBase
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour);
		void render();

	private:
		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);
		
		GLuint m_VBO;
		GLuint m_VAO;

		GlyphSortType m_sortType;

		std::vector<Glyph*> p_glyphs; // for sorting
		std::vector<Glyph> m_glyphs; // actual glyphs
		std::vector<RenderBatch> m_renderBatches;

	};
}