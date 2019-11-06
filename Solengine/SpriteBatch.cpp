#include "SpriteBatch.h"

#include <algorithm>

namespace Solengine
{
	SpriteBatch::SpriteBatch() : vertexBufferObject(0), vertexArrayObject(0)
	{
		createVertexArray();
	}

	SpriteBatch::~SpriteBatch() {}

	void SpriteBatch::Begin(GlyphSortType sType/* = GlyphSortType::TEXTURE*/)
	{
		sortType = sType;
		renderBatches.clear();
		glyphs.clear();
	}

	void SpriteBatch::End()
	{
		_glyphs.resize(glyphs.size());
		for (size_t i = 0; i < glyphs.size(); i++)
		{
			_glyphs[i] = &glyphs[i];
		}
		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour)
	{
		glyphs.emplace_back(destRect, uvRect, texture, depth, colour);
	}

	void SpriteBatch::createRenderBatches()
	{
		std::vector <Vertex> vertices;
		//reserving memory should make this faster
		//resizes based on size of glyph array
		vertices.resize(_glyphs.size() * 6);

		//.empty is same as .size == 0;
		if (_glyphs.empty()) return;
		
		//current vertex
		int cv = 0; 
		int offset = 0;
	
		renderBatches.emplace_back(offset, 6, _glyphs[0]->Texture);
		
		vertices[cv++] = _glyphs[0]->TopLeft;
		vertices[cv++] = _glyphs[0]->BottomLeft;
		vertices[cv++] = _glyphs[0]->BottomRight;
		vertices[cv++] = _glyphs[0]->BottomRight;
		vertices[cv++] = _glyphs[0]->TopRight;
		vertices[cv++] = _glyphs[0]->TopLeft;
		offset += 6;

		for (size_t cg = 1; cg < _glyphs.size(); cg++)
		{
			if (_glyphs[cg]->Texture != _glyphs[cg - 1]->Texture)
			{
				renderBatches.emplace_back(offset, 6, _glyphs[cg]->Texture);
			}
			else
			{
				renderBatches.back().NumVertices += 6;
			}

			vertices[cv++] = _glyphs[cg]->TopLeft;
			vertices[cv++] = _glyphs[cg]->BottomLeft;
			vertices[cv++] = _glyphs[cg]->BottomRight;
			vertices[cv++] = _glyphs[cg]->BottomRight;
			vertices[cv++] = _glyphs[cg]->TopRight;
			vertices[cv++] = _glyphs[cg]->TopLeft;
			offset += 6;
		}
		//bind buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		//orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		//unbind buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//Renders the entire spritebatch to screen
	void SpriteBatch::Render()
	{
		glBindVertexArray(vertexArrayObject);

		for (size_t i = 0; i < renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, renderBatches[i].Texture);

			glDrawArrays(GL_TRIANGLES, renderBatches[i].Offset, renderBatches[i].NumVertices);
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::createVertexArray()
	{
		if (vertexArrayObject == 0)
		{
			glGenVertexArrays(1, &vertexArrayObject);
		}
		glBindVertexArray(vertexArrayObject);

		if (vertexBufferObject == 0)
		{
		    glGenBuffers(1, &vertexBufferObject);
		}
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

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
		switch (sortType)
		{
		    case GlyphSortType::BACK_TO_FRONT:
			    std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
				break;
			case GlyphSortType::FRONT_TO_BACK:
				std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
				break;
			case GlyphSortType::TEXTURE:
				std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
				break;
		}	
	}

	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
	{
		return (a->Depth < b->Depth);
	}

	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
	{
		return (a->Depth > b->Depth);
	}

	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b) 
	{
		return (a->Texture < b->Texture);
	}
}