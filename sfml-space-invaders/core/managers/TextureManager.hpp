#ifndef CORE_MANAGERS_TEXTURE_MANAGER_HPP
#define CORE_MANAGERS_TEXTURE_MANAGER_HPP

#include <unordered_map>
#include <string>

#include "../Texture.hpp"

using TextureMap = std::unordered_map<std::string, Texture *>;
using TextureMapConstItr = TextureMap::const_iterator;
using TextureMapItr = TextureMap::iterator;

class TextureManager
{
public:
	TextureManager();
	TextureManager(TextureManager &) = delete;
	TextureManager(TextureManager &&) = delete;
	~TextureManager();

	std::size_t size() const noexcept;
	
	bool loadTexture(const std::string key, std::string path);
	bool hasTexture(const std::string key) const;

	Texture * getTexture(const std::string key) const;
	bool removeTexture(const std::string key);

private:
	TextureMap textures;
};

#endif // !CORE_MANAGERS_TEXTURE_MANAGER_HPP