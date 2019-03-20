#include "TextureCache.h"


#include "ImageLoader.h"

namespace Solengine
{
	TextureCache::TextureCache()
	{
	}

	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath)
	{
		//Look up the texture
		auto mit = m_textureMap.find(texturePath);

		//Check if it's not in the map
		if (mit == m_textureMap.end())
		{
			//Load the texture
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			//Insert it into the map
			m_textureMap.insert(make_pair(texturePath, newTexture));

			return newTexture;
		}
	
		return mit->second;
	}
}