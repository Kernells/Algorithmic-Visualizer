#include "Events.h"

#include <SDL.h>
#include "TextRenderer.h"
#include "Visualizer.h"

using namespace TextRenderer;
using namespace Visualizer;

bool Uppercase = false;

SDL_Event e;

// Shift + enter to run

namespace Events {
	void ProcessEvents() {
		while (SDL_PollEvent(&e)) {
			bool ValidKey = false;
			bool PushKey = true;
			if (e.type == SDL_EventType::SDL_KEYDOWN || e.type == SDL_EventType::SDL_KEYUP) {
				if (e.key.keysym.sym == 1073742049)
				{
					if (e.key.type == SDL_KEYUP) {
						if (Uppercase) {
							Uppercase = false;
						}
					}
					if (e.key.type == SDL_KEYDOWN) {
						if (!Uppercase) {
							Uppercase = true;
						}
					}
				}
			}
			if (e.type == SDL_EventType::SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case 55:
					if (Uppercase) {
						Input.push_back('/');
					}
					else {
						Input.push_back('7');
					}
					PushKey = false; // Dont push as regular key
					break;
				case 43:
					if (Uppercase) {
						Input.push_back('*');
					}
					else {
						Input.push_back('+');
					}
					PushKey = false; // Dont push as regular key
					break;
				case 48:
					if (Uppercase) {
						Input.push_back('=');
					}
					else {
						Input.push_back('0');
					}
					PushKey = false; // Dont push as regular key
					break;
				case 45:
					Input.push_back('-');
					break;
				case 13:
					if (Uppercase) {
						std::string Parameters;

						for (std::string Input : TextRenderer::StoredTexts) {
							Parameters += Input;
							Parameters += "\n";
						}

						for (std::string Input : TextRenderer::Texts) {
							Parameters += Input;
							Parameters += "\n";
						}
						Parameters = Input + Parameters;

						Visualizer::ProcessInput(Parameters);
						Visualizer::RenderText = false;
						Visualizer::RenderVisualizer = true;
					}
					else {
						TickWI = MinTickWI;
						bool LowerCurrentTextY = true;

						if (CurrentTextY + FontYIncrement > WindowHeight - FontYIncrement * 3) {
							TextRenderer::StoredTexts.push_back(TextRenderer::Texts.at(0));
							TextRenderer::Texts.erase(TextRenderer::Texts.begin());
							LowerCurrentTextY = false;
						}

						TextsYs.push_back(CurrentTextY);
						Texts.push_back(Input);
						Input.clear();

						if (LowerCurrentTextY) {
							CurrentTextY += FontYIncrement;
						}
					}
					break;
				case 44:
					Input.push_back(',');
					break;
				case 46:
					Input.push_back('.');
					break;
				case 56: // (
					if (Uppercase) {
						Input.push_back('(');
						PushKey = false; // Dont push as regular key
					}
					break;
				case 57: // )
					if (Uppercase) {
						Input.push_back(')');
						PushKey = false; // Dont push as regular key
					}
					break;
				case 8:
				{
					if (Input.length() > 0) {
						Input.pop_back();
					}
					else {
						if (CurrentTextY > 0) {
							bool ModifyFontYIncrement = true;
							if (!TextRenderer::StoredTexts.empty()) {
								Texts.insert(Texts.begin(), StoredTexts.at(0));
								StoredTexts.erase(StoredTexts.begin());
								ModifyFontYIncrement = false;
							}
							if (ModifyFontYIncrement) {
								CurrentTextY -= FontYIncrement;
							}
							Input = Texts[Texts.size() - 1];
							Texts.pop_back();
						}
					}

					ValidKey = true;

					break;
				}
				case 32:
				{
					Input.push_back(' ');
					ValidKey = true;
					break;
				}
				}

				if (e.key.keysym.sym >= SDLK_0 && e.key.keysym.sym <= SDLK_z && PushKey) {
					Input += static_cast<char>(e.key.keysym.sym);
					ValidKey = true;
				}

				if (ValidKey) {
					bool LowerCurrentTextY = true;

					if (FontIncrement * Input.length() >= WindowWidth - FontIncrement) {
						if (CurrentTextY + FontYIncrement > WindowHeight - FontYIncrement * 3){
							TextRenderer::StoredTexts.push_back(TextRenderer::Texts.at(0));
							TextRenderer::Texts.erase(TextRenderer::Texts.begin());
							LowerCurrentTextY = false;
						}
						TextsYs.push_back(CurrentTextY);
						Input.pop_back();

						Texts.push_back(Input);

						Input.clear();
						Input = static_cast<char>(e.key.keysym.sym);

						if (LowerCurrentTextY) {
							CurrentTextY += FontYIncrement;
						}

					}
					TickWI = MinTickWI;
				}


			}
			if (e.type == SDL_QUIT) Running = false;
		}
	}
}