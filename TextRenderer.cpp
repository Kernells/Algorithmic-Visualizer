#include "TextRenderer.h"
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Visualizer.h"

using namespace Visualizer;

namespace TextRenderer {


	int TextRenderer::TickWI = 0; // Tick White Indicator
	int TextRenderer::MinTickWI = 35;
	int TextRenderer::MaxTickWI = 70;

	int TextRenderer::CurrentTextY = 0;

	std::vector<int> TextRenderer::TextsYs;
	std::vector<int> TextRenderer::TextsWidths;
	std::vector<std::string> TextRenderer::Texts;
	std::vector<std::string> TextRenderer::StoredTexts;
	std::vector<SDL_Texture*> TextRenderer::Text_Textures;

	std::string TextRenderer::Input = "";

	SDL_Color font_color = { 255,255,255,255 };

	int TextRenderer::FontIncrement = 20;
	int TextRenderer::FontYIncrement = 20;

	TTF_Font* font;

	void Setup() {
		font = TTF_OpenFont("Fonts/Ticketing.ttf", 24);
		if (!font) {
			std::cout << "Unable to open font";
		}
	}

	void Render() {

		if (!Visualizer::RenderText) return;

		int TextWidth = FontIncrement * Input.length();

		for (SDL_Texture* text : Text_Textures) {
			SDL_DestroyTexture(text);
		}
		Text_Textures.clear();

		for (std::string Text : Texts) {
			SDL_Surface* textSurface = TTF_RenderText_Solid(font, Text.c_str(), font_color);
			SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Renderer, textSurface);
			SDL_FreeSurface(textSurface);
			Text_Textures.push_back(textTexture);
		}

		SDL_Surface* textSurface = TTF_RenderText_Solid(font, Input.c_str(), font_color);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Renderer, textSurface);
		SDL_FreeSurface(textSurface);

		SDL_Rect textRect;
		textRect.x = 0;
		textRect.y = CurrentTextY;
		textRect.w = TextWidth;
		textRect.h = 30;

		SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(Renderer);

		SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

		if (TickWI >= MinTickWI && TickWI <= MaxTickWI) {
			SDL_RenderDrawLine(Renderer, textRect.x + textRect.w, CurrentTextY, textRect.x + textRect.w, CurrentTextY + 30);
		}
		if (TickWI >= MaxTickWI) {
			TickWI = 0;
		}
		TickWI++;

		for (int i = 0; i < Text_Textures.size(); i++) {
			SDL_Rect textRect;
			textRect.x = 0;
			textRect.y = TextsYs.at(i);
			textRect.w = FontIncrement * Texts.at(i).length();
			textRect.h = 30;
			SDL_RenderCopy(Renderer, Text_Textures.at(i), NULL, &textRect);
		}


		SDL_RenderCopy(Renderer, textTexture, NULL, &textRect);

	}
}