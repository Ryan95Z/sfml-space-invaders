#include "Texture.hpp"

#include <SOIL2/SOIL2.h>

Texture::Texture() : has_loaded(false), texture_loc(0)
{
}

Texture::~Texture()
{
}

bool Texture::loadFromFile(std::string path)
{
	const char *c_path = path.c_str();
	texture_loc = SOIL_load_OGL_texture(
		c_path,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);
	has_loaded = true;
	return has_loaded;
}

GLuint Texture::getTextureLoc() const
{
	if (!has_loaded)
	{
		throw new TextureNotLoadedException();
	}
	return texture_loc;
}
