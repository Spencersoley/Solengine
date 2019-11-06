#include "ResourceManager.h"

namespace Solengine
{
	TextureCache ResourceManager::m_textureCache;

	GLTexture ResourceManager::GetTexture(std::string texturePath)
	{
		return m_textureCache.GetTexture(texturePath);
	}
}