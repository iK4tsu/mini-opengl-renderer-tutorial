#include "display.h"

#include <iostream>
#include <GL/glew.h>

Display::Display(unsigned int width, unsigned int height, const std::string& title)
	: closed(false)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	// this attributes can be used because the window is created with OpenGL flag
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // 8 bits for red colors
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); // 8 bits for green colors
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); // 8 bits for blue colors
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // allocates space for a second window

	this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	this->context = SDL_GL_CreateContext(this->window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "[Error] glew failed to initialize!" << std::endl;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

Display::~Display()
{
	SDL_GL_DeleteContext(this->context);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

void Display::swapBuffers()
{
	SDL_GL_SwapWindow(this->window);
}

void Display::update()
{
	swapBuffers();
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			this->closed = true;
		}
	}
}

void Display::clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
