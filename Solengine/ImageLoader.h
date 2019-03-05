#pragma once

#include <string>

#include "GLTexture.h"

namespace Solengine
{
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);
	};
}

