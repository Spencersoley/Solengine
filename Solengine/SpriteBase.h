#pragma once

#ifndef SpriteBase_h
#define SpriteBase_h

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

	class SpriteBase
	{
	public:
		SpriteBase() {};
		virtual ~SpriteBase() {};

		virtual void begin(GlyphSortType sortType = GlyphSortType::TEXTURE) = 0;
		virtual void end() = 0;
		virtual void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour) = 0;
		virtual void render() = 0;
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

}

#endif