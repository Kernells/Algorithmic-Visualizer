#include "Visualizer.h"
#include <SDL_ttf.h>
#include <iostream>
#include <random>
#include <complex>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <commdlg.h>

extern "C" {
#include "Dependencies/LUA/lua.h"
#include "Dependencies/LUA/lauxlib.h"
#include "Dependencies/LUA/lualib.h"
}

namespace Visualizer {

	int Visualizer::WindowWidth = 650;
	int Visualizer::WindowHeight = 500;

	bool Visualizer::Running = true;

	SDL_Window* Visualizer::Window = nullptr;
	SDL_Renderer* Visualizer::Renderer = nullptr;

	SDL_Surface* Visualizer::Surface = nullptr;

	bool RenderText = true;
	bool RenderVisualizer = false;

	lua_State* LuaState;

	std::wstring OpenFileDialog()
	{
		wchar_t filename[MAX_PATH] = L"";

		OPENFILENAMEW ofn = {};
		ofn.lStructSize = sizeof(ofn);
		ofn.lpstrFile = filename;
		ofn.nMaxFile = MAX_PATH;

		ofn.lpstrFilter =
			L"Lua Files (*.lua)\0*.lua\0"
			L"All Files (*.*)\0*.*\0";

		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetOpenFileNameW(&ofn))
			return std::wstring(filename);

		return L"";
	}

	std::string WStringToUTF8(const std::wstring& wstr)
	{
		if (wstr.empty()) return "";

		int sizeNeeded = WideCharToMultiByte(
			CP_UTF8, 0,
			wstr.c_str(),
			(int)wstr.size(),
			NULL, 0,
			NULL, NULL);

		std::string result(sizeNeeded, 0);

		WideCharToMultiByte(
			CP_UTF8, 0,
			wstr.c_str(),
			(int)wstr.size(),
			&result[0],
			sizeNeeded,
			NULL, NULL);

		return result;
	}

	std::string getFileContents(const std::string& filepath)
	{
		std::ifstream file(filepath, std::ios::binary | std::ios::ate);
		if (!file)
			return "";

		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		std::string buffer(size, '\0');
		file.read(&buffer[0], size);

		return buffer;
	}

	enum ObjectType {
		LINE
	};

	struct Object {
		ObjectType ObjType;
		SDL_Rect ObjRect;
	};

	std::vector<Object> RenderObjects;

	int R = 0;
	int G = 0;
	int B = 0;
	int A = 0;

	static int setcolor(lua_State* L) {
		if (lua_gettop(L) < 4) {
			std::cout << "setcolor expects 4 values\n";
			return 0;
		}
		R = luaL_checknumber(L, 1);
		G = luaL_checknumber(L, 2);
		B = luaL_checknumber(L, 3);
		A = luaL_checknumber(L, 4);

		return 0;
	}

	static int renderline(lua_State* L) {
		if (lua_gettop(L) < 4) {
			std::cout << "renderline expects 4 values\n";
			return 0;
		}
		int minx = luaL_checknumber(L, 1);
		int maxx = luaL_checknumber(L, 2);
		int miny = luaL_checknumber(L, 3);
		int maxy = luaL_checknumber(L, 4);

		Object line;
		SDL_Rect linerect;
		linerect.w = minx;
		linerect.x = maxx;
		linerect.h = miny;
		linerect.y = maxy;

		line.ObjRect = linerect;
		line.ObjType = LINE;

		RenderObjects.push_back(line);

		return 0;
	}

	static int loadfile(lua_State* L) {
		if (lua_gettop(L) > 0) {
			std::cout << "loadfile doesn't expect any value\n";
			return 0;
		}
		
		std::string path = WStringToUTF8(OpenFileDialog());
		if (!path.empty())
		{
			std::string code = getFileContents(path);

			ProcessInput(code);
		}

		return 0;
	}

	void Visualizer::ProcessInput(std::string Parameters) {

		if (luaL_dostring(LuaState, Parameters.c_str()) != LUA_OK) {
			std::cout << lua_tostring(LuaState, 1);
		}
	}

	void Visualizer::Visualize() {
		if (!RenderVisualizer) return;
		for (Object obj : RenderObjects) {
			switch (obj.ObjType) {
			case LINE:
			{
				SDL_Rect objrect = obj.ObjRect;

				SDL_SetRenderDrawColor(Visualizer::Renderer, R, G, B, A);
				SDL_SetRenderDrawBlendMode(Visualizer::Renderer, SDL_BLENDMODE_BLEND);
				SDL_RenderDrawLine(Visualizer::Renderer, objrect.w, objrect.h, objrect.x, objrect.y); 
			}
			}
		}
	}

	void Init() {
		SDL_Init(SDL_INIT_VIDEO);
		if (TTF_Init() == -1) {
			std::cout << "Unable to initialize TTF";
		}

		Window = SDL_CreateWindow("Algorithmic Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight, 0);
		Renderer = SDL_CreateRenderer(Window, 0, 0);

		if (Renderer == nullptr) {
			std::cout << "Unable to create renderer";
			return;
		}

		LuaState = luaL_newstate();
		luaL_openlibs(LuaState);

		// Custom rendering support

		lua_register(LuaState,"renderline", renderline);
		lua_register(LuaState, "setcolor", setcolor);
		lua_register(LuaState, "loadfile", loadfile);
	}
}