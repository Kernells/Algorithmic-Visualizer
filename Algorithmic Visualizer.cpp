#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include "TextRenderer.h"
#include "Visualizer.h"
#include "Events.h"

void InitSDL() {

	Visualizer::Init();
	TextRenderer::Setup();

	while (Visualizer::Running){
		
		SDL_SetRenderDrawColor(Visualizer::Renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(Visualizer::Renderer);

		TextRenderer::Render();
		Visualizer::Visualize();

		SDL_Delay(16); // ~ 60 fps

		SDL_RenderPresent(Visualizer::Renderer);

		Events::ProcessEvents();
	}
}

int main()
{
	InitSDL();
	return 0;
}
