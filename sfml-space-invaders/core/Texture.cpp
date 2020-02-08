#include "Texture.hpp"

#include <iostream>
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
		SOIL_LOAD_RGB
	);

	std::cout << SOIL_last_result() << std::endl;

	has_loaded = true;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_loc);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
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
