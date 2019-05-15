#pragma once

#include "SpriteBase.h"

namespace Solengine
{
	class RenderSingle
	{
	public:
		RenderSingle() : numVertices(6) {};

		GLuint numVertices;
		GLuint texture;
	};

	class SpriteSingle : public SpriteBase
	{
	public:
		SpriteSingle();
		~SpriteSingle();

		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE) {};
		void end();
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour);
		void render();

	private:
		void createRenderSingle();
		void createVertexArray();

		GLuint m_VBO;
		GLuint m_VAO;

		Glyph m_glyph;

		RenderSingle m_renderSingle;

	};
}