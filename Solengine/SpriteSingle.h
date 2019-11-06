#pragma once

#include "SpriteBase.h"
#include "RenderSingle.h"

namespace Solengine
{
	class SpriteSingle : public SpriteBase
	{
	public:
		SpriteSingle();
		~SpriteSingle();

		void Begin(GlyphSortType sortType = GlyphSortType::TEXTURE) {};
		
		void End();
		
		void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour);
		
		void Render();

	private:
		void createRenderSingle();
		
		void createVertexArray();

		GLuint vertexBufferObject;
		
		GLuint vertexArrayObject;

		Glyph glyph;

		RenderSingle renderSingle;
	};
}