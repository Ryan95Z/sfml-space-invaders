#include <iostream>

#include "GlmLogger.hpp"

void GlmLogger::vec3(glm::vec3 vec) const
{
	std::cout << vec.x << ", " << vec.y << ", " << vec.z << std::endl;
}

void GlmLogger::mat4(glm::mat4 matrix) const
{
	const int n = 4;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
