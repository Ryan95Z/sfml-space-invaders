#include "TextureManager.hpp"

TextureManager::TextureManager() {}

TextureManager::~TextureManager()
{
	while (textures.begin() != textures.end())
	{
		delete textures.begin()->second;
		textures.begin()->second = nullptr;
		textures.erase(textures.begin());
	}
	textures.clear();
}

std::size_t TextureManager::size() const noexcept
{
	return textures.size();
}

bool TextureManager::loadTexture(const std::string key, std::string path)
{
	Texture *t = new Texture();
	if (!t->loadFromFile(path)) { return false; }
	textures.emplace(key, t);
	return true;
}

bool TextureManager::hasTexture(const std::string key) const
{
	return textures.find(key) != textures.end();
}

Texture * TextureManager::getTexture(const std::string key) const
{
	TextureMapConstItr itr = textures.find(key);
	if (itr == textures.end()) { return nullptr; }
	return itr->second;
}

bool TextureManager::removeTexture(const std::string key)
{
	TextureMapItr itr = textures.find(key);
	if (itr == textures.end()) { return true; }
	delete itr->second;
	itr->second = nullptr;
	textures.erase(itr);
	return true;
}