#pragma once

#include <string>

#include "TextureCache.h"

namespace Solengine
{
	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string texturePath);

	private:
		static TextureCache _textureCache;
	};
}

