#include "SpriteSingle.h"

#include <algorithm>

namespace Solengine
{
	SpriteSingle::SpriteSingle() : vertexBufferObject(0), vertexArrayObject(0)
	{
		createVertexArray();
	}

	SpriteSingle::~SpriteSingle() {}

	void SpriteSingle::End()
	{
		createRenderSingle();
	}

	void SpriteSingle::Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColourRGBA8& colour)
	{
		Glyph newGlyph(destRect, uvRect, texture, depth, colour);
		glyph = newGlyph;
	}

	void SpriteSingle::createRenderSingle()
	{
		std::vector <Vertex> vertices(6);
		//reserving memory should make this faster

		//current vertex
		int cv = 0;
		
		renderSingle.Texture = glyph.Texture;

		vertices[cv++] = glyph.TopLeft;
		vertices[cv++] = glyph.BottomLeft;
		vertices[cv++] = glyph.BottomRight;
		vertices[cv++] = glyph.BottomRight;
		vertices[cv++] = glyph.TopRight;
		vertices[cv++] = glyph.TopLeft;

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
	void SpriteSingle::Render()
	{
		glBindVertexArray(vertexArrayObject);

		glBindTexture(GL_TEXTURE_2D, renderSingle.Texture);

		glDrawArrays(GL_TRIANGLES, 0, renderSingle.NumVertices);	

		glBindVertexArray(0);
	}

	void SpriteSingle::createVertexArray()
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
}