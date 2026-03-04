#pragma once

#include <SDL.h>
#include <string>
#include <iostream>

namespace Visualizer
{
	extern SDL_Window* Window;
	extern SDL_Renderer* Renderer;

	extern int WindowWidth;
	extern int WindowHeight;

	extern bool Running;

	extern SDL_Surface* Surface;
    
	extern bool RenderText;
	extern bool RenderVisualizer;

	void ProcessInput(std::string Parameters);
	void Visualize();

	void Init();
}

