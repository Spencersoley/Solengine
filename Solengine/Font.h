#pragma once

#include <SDL_TTF/SDL_ttf.h>

#include <glm/glm.hpp>
#include <map>
#include <vector>

#include "Vertex.h"
#include "SpriteBatch.h"

namespace Solengine
{
	struct GLTexture;
	class SpriteBatch;

	struct CharGlyph
	{
	public:
		char character;
		glm::vec4 uvRect;
		glm::vec2 size;
	};

#define FIRST_PRINTABLE_CHAR ((char)32)
#define LAST_PRINTABLE_CHAR ((char)126)

	enum class Justification
	{
		LEFT, MIDDLE, RIGHT
	};

	class Font
	{
	public:
		Font(const char* font, int size, char cs, char ce, SpriteBatch* spriteBatch);
		Font(const char* font, int size, SpriteBatch* spriteBatch) :
			Font(font, size, FIRST_PRINTABLE_CHAR, LAST_PRINTABLE_CHAR, spriteBatch)
		{
		}
		
		void init(const char* font, int size);
		void init(const char* font, int size, char cs, char ce);

		void dispose();

		int getFontHeight() const { return m_fontHeight; }

		glm::vec2 measure(const char* s);

		void draw(const char* s, glm::vec2 position, glm::vec2 scaling, float depth, ColourRGBA8 tint, Justification just = Justification::LEFT);

		Solengine::SpriteBatch* getSpriteBatch() { return p_SOL_SB; }

	private: 
		static std::vector<int>* createRows(glm::ivec4* rects, int rectsLength, int r, int padding, int& w);

		Solengine::SpriteBatch* p_SOL_SB = nullptr;

		int m_regStart, m_regLength;
		CharGlyph* p_glyphs;
		int m_fontHeight;

		unsigned int m_texID;
	};

}