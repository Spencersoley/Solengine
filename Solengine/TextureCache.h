#pragma once
#include <iostream>
#include <map>

#include "GLTexture.h"

//This will cache textures, so multiple sprites can use the same texture

namespace Solengine
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture GetTexture(std::string);

	private:
		std::map<std::string, GLTexture> m_textureMap;
	};
}