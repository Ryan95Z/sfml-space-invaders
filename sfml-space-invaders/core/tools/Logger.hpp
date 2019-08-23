#ifndef CORE_TOOLS_LOGGER
#define CORE_TOOLS_LOGGER

#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include <vector>


class Logger
{
public:
	static void debug(std::string msg) noexcept
	{
		std::cout << "[DEBUG]: " << msg << std::endl;
	}

	static void debug(int i) noexcept
	{
		std::cout << "[DEBUG]: Int -> " << i << std::endl;
	}

	static void debug(float f) noexcept
	{
		std::cout << "[DEBUG]: Float -> " << f << std::endl;
	}

	static void debug(double v) noexcept
	{
		std::cout << "[DEBUG]: Double -> " << v << std::endl;
	}

	static void debug(short s) noexcept
	{
		std::cout << "[DEBUG]: Short -> " << s << std::endl;
	}

	static void debug(glm::vec3 vec) noexcept
	{
		std::cout << "[DEBUG]: Vec3 -> (" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
	}

	static void debug(glm::mat4 matrix) noexcept
	{
		const int n = 4;
		std::cout << "[DEBUG]: Mat4 -> \n";
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				std::cout << matrix[i][j] << " ";
			}
			std::cout << "\n" << std::endl;
		}
	}
	
	static void error(std::string msg) noexcept
	{
		std::cout << "[ERROR]: " << msg << std::endl;
	}
};

#endif // CORE_TOOLS_LOGGER