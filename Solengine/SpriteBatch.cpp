#include "SpriteBatch.h"

#include <algorithm>

namespace Solengine
{
	SpriteBatch::SpriteBatch() : _vbo(0), _vao(0)
	{

	}

	SpriteBatch::~SpriteBatch()
	{

	}

	void SpriteBatch::init()
	{
		createVertexArray();
	}

	void SpriteBatch::begin(GlyphSortType sortType/* = GlyphSortType::TEXTURE*/)
	{
		_sortType = sortType;
		_renderBatches.clear();
		_glyphs.clear();
	}

	void SpriteBatch::end()
	{
		_pGlyphs.resize(_glyphs.size());
		for (size_t i = 0; i < _glyphs.size(); i++)
		{
			_pGlyphs[i] = &_glyphs[i];
		}
		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour)
	{
		_glyphs.emplace_back(destRect, uvRect, texture, depth, colour);
	}

	void SpriteBatch::createRenderBatches()
	{
		std::vector <Vertex> vertices;
		//reserving memory should make this faster
		//resizes based on size of glyph array
		vertices.resize(_pGlyphs.size() * 6);

		//.empty is same as .size == 0;
		if (_pGlyphs.empty()) return;
		
		//current vertex
		int cv = 0; 
		int offset = 0;
	
		_renderBatches.emplace_back(offset, 6, _pGlyphs[0]->texture);
		
		vertices[cv++] = _pGlyphs[0]->topLeft;
		vertices[cv++] = _pGlyphs[0]->bottomLeft;
		vertices[cv++] = _pGlyphs[0]->bottomRight;
		vertices[cv++] = _pGlyphs[0]->bottomRight;
		vertices[cv++] = _pGlyphs[0]->topRight;
		vertices[cv++] = _pGlyphs[0]->topLeft;
		offset += 6;

		for (size_t cg = 1; cg < _pGlyphs.size(); cg++)
		{
			if (_pGlyphs[cg]->texture != _pGlyphs[cg - 1]->texture)
			{
				_renderBatches.emplace_back(offset, 6, _pGlyphs[cg]->texture);
			}
			else
			{
				_renderBatches.back().numVertices += 6;
			}

			vertices[cv++] = _pGlyphs[cg]->topLeft;
			vertices[cv++] = _pGlyphs[cg]->bottomLeft;
			vertices[cv++] = _pGlyphs[cg]->bottomRight;
			vertices[cv++] = _pGlyphs[cg]->bottomRight;
			vertices[cv++] = _pGlyphs[cg]->topRight;
			vertices[cv++] = _pGlyphs[cg]->topLeft;
			offset += 6;
		}
		//bind buffer
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		//orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		//unbind buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//Renders the entire spritebatch to screen
	void SpriteBatch::renderBatch()
	{
		glBindVertexArray(_vao);

		for (size_t i = 0; i < _renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

			glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::createVertexArray()
	{
		if (_vao == 0)
		{
			glGenVertexArrays(1, &_vao);
		}
		glBindVertexArray(_vao);

		if (_vbo == 0)
		{
		    glGenBuffers(1, &_vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		//Tells opengl to use the first attrib array.
		//We only need this for now as we're only using position.
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//This is the position attribute pointer.
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		//This is the colour attribute pointer.
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));
		//This is the UV attribute pointer.
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}

	void SpriteBatch::sortGlyphs() 
	{
		switch (_sortType)
		{
		    case GlyphSortType::BACK_TO_FRONT:
			    std::stable_sort(_pGlyphs.begin(), _pGlyphs.end(), compareBackToFront);
				break;
			case GlyphSortType::FRONT_TO_BACK:
				std::stable_sort(_pGlyphs.begin(), _pGlyphs.end(), compareFrontToBack);
				break;
			case GlyphSortType::TEXTURE:
				std::stable_sort(_pGlyphs.begin(), _pGlyphs.end(), compareTexture);
				break;
		}	
	}

	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
	{
		return (a->depth < b->depth);
	}

	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
	{
		return (a->depth > b->depth);
	}

	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b) 
	{
		return (a->texture < b->texture);
	}
}