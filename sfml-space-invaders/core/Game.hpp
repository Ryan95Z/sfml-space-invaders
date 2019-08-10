#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include "Window.hpp"
#include "Shader.hpp"
#include "Triangle.hpp"

class Game
{
public:
	Game();
	~Game();

	bool isOpen() const;

	void render();
	void update();
	void handleEvents();
private:
	Triangle *triangle;
	Window window;
};

#endif // CORE_GAME_HPP