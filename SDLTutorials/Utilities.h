#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SDL.h>
#include <map>
#include <SDL_ttf.h>
#include <memory>
#include <string>

class AssetManager {
private: 
	std::map<const char*, TTF_Font*> fonts;
public:
	static SDL_Texture* LoadTexture(const char* filename, SDL_Renderer* ren);

	void AddFont(const char* id_, const char* path_, const int size_);
	void CloseFonts();
	TTF_Font* GetFont(const char* id_);
	std::unique_ptr<SDL_Color> MakeColor(Uint8 r_, Uint8 g_, Uint8 b_, Uint8 a_);
	std::unique_ptr<SDL_Color> MakeColor(Uint8 r_, Uint8 g_, Uint8 b_);
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

