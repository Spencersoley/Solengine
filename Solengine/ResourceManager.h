#pragma once

#include <string>

#include "TextureCache.h"

namespace Solengine
{
	class ResourceManager
	{
	public:
		static GLTexture GetTexture(std::string texturePath);

	private:
		static TextureCache m_textureCache;
	};
}

