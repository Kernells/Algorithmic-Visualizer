#pragma once
#include <SDL.h>
#include <string>
#include <vector>
namespace TextRenderer
{
	extern int FontIncrement;
	extern int FontYIncrement;

	extern int CurrentTextY;

	extern int TickWI;
	extern int MinTickWI;
	extern int MaxTickWI;

	extern std::vector<int> TextsYs;
	extern std::vector<int> TextsWidths;
	extern std::vector<std::string> Texts;
	extern std::vector<std::string> StoredTexts;
	extern std::vector<SDL_Texture*> Text_Textures;

	extern std::string Input;

	void Setup();
	void Render();
}

