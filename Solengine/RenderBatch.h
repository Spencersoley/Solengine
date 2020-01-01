#include <GL\glew.h>

namespace Solengine
{
	class RenderBatch
	{
	public:
		RenderBatch(GLuint offst, GLuint numVerts, GLuint txtr) :
			Offset(offst),
			NumVertices(numVerts),
			Texture(txtr)
		{}

		GLuint Offset;
		GLuint NumVertices;
		GLuint Texture;
	};
}