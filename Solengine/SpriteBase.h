#ifndef SpriteBase_h
#define SpriteBase_h

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Vertex.h"
#include "Glyph.h"

namespace Solengine
{
	class SpriteBase
	{
	public:
		SpriteBase() {};
		virtual ~SpriteBase() {};

		virtual void Begin(GlyphSortType sortType = GlyphSortType::TEXTURE) = 0;
		virtual void End() = 0;
		virtual void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour) = 0;
		virtual void Render() = 0;
	};
}

#endif