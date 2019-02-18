#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SDL/SDL.h>
#include <map>
#include <SDL/SDL_ttf.h>
#include <memory>
#include <string>
#include "Geometry.h"

class AssetManager {
private: 
	std::map<const char*, TTF_Font*> fonts;
	//std::map<int, std::unique_ptr<SDL_Color>> colors;
public:
	enum Color {Red, Green, Blue, Yellow, Orange, Purple, Indigo, NavyBlue, Violet, FireRed, LightGrey, Grey, SlateGrey, DarkGrey, Black, White} e_Color;
	static SDL_Texture* LoadTexture(const char* filename, SDL_Renderer* ren);

	//AssetManager();

	void AddFont(const char* id_, const char* path_, const int size_);
	void CloseFonts();
	TTF_Font* GetFont(const char* id_);
	std::unique_ptr<SDL_Color> MakeColor(Uint8 r_, Uint8 g_, Uint8 b_, Uint8 a_);
	std::unique_ptr<SDL_Color> MakeColor(Uint8 r_, Uint8 g_, Uint8 b_);
	std::unique_ptr<SDL_Color> GetColor(int id);
};

struct MouseController {
	static int x, y;
	static bool primaryButton, secondaryButton;
	static bool doubleClicks;
};

class Time {
private:
	static float time;
public:
	static int seconds, minutes, hours;
	static void SetTime(int s_, int m_, int h_);
	static void Update(const float deltaTime);
	static void Reset();
	static std::string ToString();
};

#endif 

