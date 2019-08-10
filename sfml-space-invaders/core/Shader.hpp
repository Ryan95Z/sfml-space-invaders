#ifndef CORE_SHADER_HPP
#define CORE_SHADER_HPP

#include <SFML/OpenGL.hpp>

#include <string>

class Shader
{
public:
	Shader(std::string vertexPath, std::string fragPath);
	~Shader();

	const GLuint id() const;
private:
	std::string readFile(const std::string filePath);

	GLuint shaderId;
};

#endif // CORE_SHADER_HPP