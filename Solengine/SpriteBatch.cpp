#include "SpriteBatch.h"

#include <algorithm>

namespace Solengine
{
	SpriteBatch::SpriteBatch() : m_VBO(0), m_VAO(0)
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
		m_sortType = sortType;
		m_renderBatches.clear();
		m_glyphs.clear();
	}

	void SpriteBatch::end()
	{
		p_glyphs.resize(m_glyphs.size());
		for (size_t i = 0; i < m_glyphs.size(); i++)
		{
			p_glyphs[i] = &m_glyphs[i];
		}
		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour)
	{
		m_glyphs.emplace_back(destRect, uvRect, texture, depth, colour);
	}

	void SpriteBatch::createRenderBatches()
	{
		std::vector <Vertex> vertices;
		//reserving memory should make this faster
		//resizes based on size of glyph array
		vertices.resize(p_glyphs.size() * 6);

		//.empty is same as .size == 0;
		if (p_glyphs.empty()) return;
		
		//current vertex
		int cv = 0; 
		int offset = 0;
	
		m_renderBatches.emplace_back(offset, 6, p_glyphs[0]->texture);
		
		vertices[cv++] = p_glyphs[0]->topLeft;
		vertices[cv++] = p_glyphs[0]->bottomLeft;
		vertices[cv++] = p_glyphs[0]->bottomRight;
		vertices[cv++] = p_glyphs[0]->bottomRight;
		vertices[cv++] = p_glyphs[0]->topRight;
		vertices[cv++] = p_glyphs[0]->topLeft;
		offset += 6;

		for (size_t cg = 1; cg < p_glyphs.size(); cg++)
		{
			if (p_glyphs[cg]->texture != p_glyphs[cg - 1]->texture)
			{
				m_renderBatches.emplace_back(offset, 6, p_glyphs[cg]->texture);
			}
			else
			{
				m_renderBatches.back().numVertices += 6;
			}

			vertices[cv++] = p_glyphs[cg]->topLeft;
			vertices[cv++] = p_glyphs[cg]->bottomLeft;
			vertices[cv++] = p_glyphs[cg]->bottomRight;
			vertices[cv++] = p_glyphs[cg]->bottomRight;
			vertices[cv++] = p_glyphs[cg]->topRight;
			vertices[cv++] = p_glyphs[cg]->topLeft;
			offset += 6;
		}
		//bind buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
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
		glBindVertexArray(m_VAO);

		for (size_t i = 0; i < m_renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);

			glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numVertices);
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::createVertexArray()
	{
		if (m_VAO == 0)
		{
			glGenVertexArrays(1, &m_VAO);
		}
		glBindVertexArray(m_VAO);

		if (m_VBO == 0)
		{
		    glGenBuffers(1, &m_VBO);
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

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
		switch (m_sortType)
		{
		    case GlyphSortType::BACK_TO_FRONT:
			    std::stable_sort(p_glyphs.begin(), p_glyphs.end(), compareBackToFront);
				break;
			case GlyphSortType::FRONT_TO_BACK:
				std::stable_sort(p_glyphs.begin(), p_glyphs.end(), compareFrontToBack);
				break;
			case GlyphSortType::TEXTURE:
				std::stable_sort(p_glyphs.begin(), p_glyphs.end(), compareTexture);
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