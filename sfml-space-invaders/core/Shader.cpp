#include "Shader.hpp"

#include <sstream>
#include <fstream>
#include <iostream>

#define BUFFER_SIZE 512


Shader::Shader(std::string vertexPath, std::string fragPath)
{
	int success;
	char infoLog[BUFFER_SIZE];
	GLuint vertexShader, fragShader;

	std::string vertex = readFile(vertexPath);
	std::string frag = readFile(fragPath);

	const char *vertexShaderSrc = vertex.c_str();
	const char *fragShaderSrc = frag.c_str();

	// Create and compile the vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShader);
	
	// Check for errors in the vertex shader
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, BUFFER_SIZE, NULL, infoLog);
		std::cout << "Error compiling vertex shader: " << vertexPath << "\n" <<  infoLog << std::endl;
	}

	// Create and compile fragment shader
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
	glCompileShader(fragShader);

	// Check for errors in the fragement shader
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, BUFFER_SIZE, NULL, infoLog);
		std::cout << "Error compiling fragment shader: " << fragPath << "\n" << infoLog << std::endl;
	}

	// Link the shaders to the program
	shaderId = glCreateProgram();
	glAttachShader(shaderId, vertexShader);
	glAttachShader(shaderId, fragShader);
	glLinkProgram(shaderId);

	// Check for compiling errors in the shader program
	glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderId, BUFFER_SIZE, NULL, infoLog);
		std::cout << "Error linking shader program: \n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);	
}

Shader::~Shader()
{
}

const GLuint Shader::id() const
{
	return shaderId;
}

std::string Shader::readFile(const std::string filePath)
{
	std::ifstream shaderFile;
	std::stringstream ss;

	shaderFile.open(filePath);
	ss << shaderFile.rdbuf();
	shaderFile.close();
	return ss.str();
}
