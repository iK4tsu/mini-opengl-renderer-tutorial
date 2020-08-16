#pragma once

#include <string>
#include <SDL2/SDL.h>

class Display
{
public:
	Display(unsigned int width, unsigned int height, const std::string& title);
	~Display();

	void swapBuffers();
	void update();
	void clear(float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.f);
	inline bool isClosed() const { return closed; }

private:
	SDL_Window* window;
	SDL_GLContext context;
	bool closed;
};
