#ifndef CORE_TEXTURE_HPP
#define CORE_TEXTURE_HPP

#include <string>
#include <exception>
#include <GL/glew.h>

class TextureNotLoadedException : public std::runtime_error
{
public:
	TextureNotLoadedException() : std::runtime_error("A texture has not been loaded yet!") {}
};

class Texture
{
public:
	Texture();

	Texture(Texture &) = delete;
	Texture(Texture &&) = delete;
	~Texture();

	bool loadFromFile(std::string path);
	GLuint getTextureLoc() const;
private:
	bool has_loaded;
	GLuint texture_loc;
};

#endif // !CORE_TEXTURE_HPP