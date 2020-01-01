#include <GL\glew.h>

namespace Solengine
{
	class RenderSingle
	{
	public:
		RenderSingle() :
			NumVertices(6),
			Texture()
		{}

		GLuint NumVertices;
		GLuint Texture;
	};
}