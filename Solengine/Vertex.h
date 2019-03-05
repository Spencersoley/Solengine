#pragma once

#include <GL/glew.h>

//No cpp file required since Vertex won't include any methods, just data
//Make vertex structs as small as possible as it makes transfer to the gpu fast as possible
//We create structs of the given type and then create an instance of each.

namespace Solengine
{
	struct Position
	{
		float x;
		float y;
	};

	struct ColourRGBA8
	{
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a; //remember: GLubyte is the same as an unsigned char
	};

	struct UV
	{
		float u;
		float v;
	};

	struct Vertex
	{
		Position position;
		ColourRGBA8 colour;
		UV uv;
		//this is 8 + 4 bytes. It's desirable to have a multiple of 4 for alignment purposes.

		void setPosition(float x, float y)
		{
			position.x = x;
			position.y = y;
		}

		void setColourRGBA8(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			colour.r = r;
			colour.g = g;
			colour.b = b;
			colour.a = a;
		}

		void setUV(float u, float v)
		{
			uv.u = u;
			uv.v = v;
		}
	};
}