#ifndef CORE_TOOLS_LOGGER
#define CORE_TOOLS_LOGGER

#include <string>
#include <iostream>
#include <cstring>
#include <ctime>

template <class T>
class Logger
{
public:
	Logger() = delete;
	Logger(Logger &) = delete;

	Logger(T *instance) : instance(instance) {}
	
	~Logger() {}

	void info(std::string msg) const noexcept
	{
		std::cout << "(" << typeid(*instance).name() << ") " << msg << std::endl;
	}
	
	void debug(std::string msg) const noexcept
	{
		std::cout << "[DEBUG]: " << "(" << typeid(*instance).name() << ") " << msg << std::endl;
	}

	void debug(float f) const noexcept
	{
		std::cout << "[DEBUG]: " << "(" << typeid(*instance).name() << ") " << f << std::endl;
	}
	
	void error(std::string msg) const noexcept
	{
		std::cerr << "[ERROR]: " << "(" << typeid(*instance).name() << ") " << msg << std::endl;
	}

private:
	T *instance;
};

#endif // CORE_TOOLS_LOGGER