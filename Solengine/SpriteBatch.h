#pragma once

#include "SpriteBase.h"
#include "RenderBatch.h"

namespace Solengine
{
	class SpriteBatch : public SpriteBase
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void Begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void End();
		void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour);
		void Render();

	private:
		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);
		
		GLuint vertexBufferObject;
		GLuint vertexArrayObject;

		GlyphSortType sortType;

		std::vector<Glyph*> _glyphs; // for sorting
		std::vector<Glyph> glyphs; // actual glyphs
		std::vector<RenderBatch> renderBatches;
	};
}