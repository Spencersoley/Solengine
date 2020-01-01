#include <glm/glm.hpp>
#include "Vertex.h"
#include <glm\ext\vector_float4.hpp>

namespace Solengine
{
	enum class GlyphSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	class Glyph //DrawnSprite?
	{
	public:
		Glyph() {}
		Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint txtr, float dpth, const ColourRGBA8& clr) :
			Texture(txtr),
			Depth(dpth)
		{
			TopLeft.colour = clr;
			TopLeft.setPosition(destRect.x, destRect.y + destRect.w);
			TopLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

			BottomLeft.colour = clr;
			BottomLeft.setPosition(destRect.x, destRect.y);
			BottomLeft.setUV(uvRect.x, uvRect.y);

			BottomRight.colour = clr;
			BottomRight.setPosition(destRect.x + destRect.z, destRect.y);
			BottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

			TopRight.colour = clr;
			TopRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
			TopRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
		}

		GLuint Texture;
		float Depth;

		Vertex TopLeft;
		Vertex BottomLeft;
		Vertex TopRight;
		Vertex BottomRight;
	};
}