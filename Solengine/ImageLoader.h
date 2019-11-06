#pragma once

#include <string>

#include "GLTexture.h"

namespace Solengine
{
	class ImageLoader
	{
	public:
		static GLTexture LoadPNG(std::string filePath);
	};
}

