#include "TextureCache.h"

#include "ImageLoader.h"

namespace Solengine
{
	TextureCache::TextureCache(){}

	TextureCache::~TextureCache(){}

	GLTexture TextureCache::GetTexture(std::string texturePath)
	{
		//Look up the texture
		auto texture = m_textureMap.find(texturePath);

		//Check if it's not in the map
		if (texture == m_textureMap.end())
		{
			//Load the texture
			GLTexture newTexture = ImageLoader::LoadPNG(texturePath);

			//Insert it into the map
			m_textureMap.insert(make_pair(texturePath, newTexture));

			return newTexture;
		}
	
		return texture->second;
	}
}