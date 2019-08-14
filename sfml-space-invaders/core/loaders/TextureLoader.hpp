#ifndef CORE_LOADERS_TEXTURE_LOADER_HPP
#define CORE_LOADERS_TEXTURE_LOADER_HPP

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

class TextureLoader
{
public:
	static GLuint loadTexture(const char *texture_path);
};

#endif // CORE_LOADERS_TEXTURE_LOADER_HPP