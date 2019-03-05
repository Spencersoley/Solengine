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
		auto mit = _textureMap.find(texturePath);

		//Check if it's not in the map
		if (mit == _textureMap.end())
		{
			//Load the texture
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			//Insert it into the map
			_textureMap.insert(make_pair(texturePath, newTexture));

			return newTexture;
		}
	
		return mit->second;
	}
}