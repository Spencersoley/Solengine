#include "SpriteSingle.h"

#include <algorithm>

namespace Solengine
{
	SpriteSingle::SpriteSingle() : m_VBO(0), m_VAO(0)
	{
		createVertexArray();
	}

	SpriteSingle::~SpriteSingle() {}

	void SpriteSingle::end()
	{
		createRenderSingle();
	}

	void SpriteSingle::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour)
	{
		Glyph newGlyph(destRect, uvRect, texture, depth, colour);
		m_glyph = newGlyph;
	}

	void SpriteSingle::createRenderSingle()
	{
		std::vector <Vertex> vertices(6);
		//reserving memory should make this faster

		//current vertex
		int cv = 0;
		
		m_renderSingle.texture = m_glyph.texture;

		vertices[cv++] = m_glyph.topLeft;
		vertices[cv++] = m_glyph.bottomLeft;
		vertices[cv++] = m_glyph.bottomRight;
		vertices[cv++] = m_glyph.bottomRight;
		vertices[cv++] = m_glyph.topRight;
		vertices[cv++] = m_glyph.topLeft;

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
	void SpriteSingle::render()
	{
		glBindVertexArray(m_VAO);

		glBindTexture(GL_TEXTURE_2D, m_renderSingle.texture);

		glDrawArrays(GL_TRIANGLES, 0, m_renderSingle.numVertices);	

		glBindVertexArray(0);
	}

	void SpriteSingle::createVertexArray()
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
}