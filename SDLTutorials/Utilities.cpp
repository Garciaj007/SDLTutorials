#include "Utilities.h"
#include <SDL_image.h>
#include <algorithm>

//------------------------------------------- Asset Manager ----------------------------------------------

SDL_Texture* AssetManager::LoadTexture(const char* filename, SDL_Renderer* ren) {
	SDL_Surface* tempSurface = IMG_Load(filename);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}

std::unique_ptr<SDL_Color> AssetManager::MakeColor(Uint8 r_, Uint8 g_, Uint8 b_, Uint8 a_) {
	std::unique_ptr<SDL_Color> color = std::make_unique<SDL_Color>();
	*color = {r_, g_, b_, a_};
	return color;
}

std::unique_ptr<SDL_Color> AssetManager::MakeColor(Uint8 r_, Uint8 g_, Uint8 b_) {
	std::unique_ptr<SDL_Color> color = std::make_unique<SDL_Color>();
	*color = { r_, g_, b_};
	return color;
}

void AssetManager::AddFont(const char* id_, const char* path_, const int size_) {
	fonts.emplace(id_, TTF_OpenFont(path_, size_));
}

void AssetManager::CloseFonts() {
	for (auto it = fonts.begin(); it != fonts.end(); it++) {
		TTF_CloseFont(it->second);
	}
	fonts.erase(fonts.begin(), fonts.end());
}

TTF_Font* AssetManager::GetFont(const char* id_) {
	return fonts.find(id_)->second;
}

//--------------------------------------------- Mouse Controller --------------------------------------------------

int MouseController::x;
int MouseController::y;
bool MouseController::primaryButton;
bool MouseController::secondaryButton;
bool MouseController::doubleClicks;

//-------------------------------------------------- Time ---------------------------------------------------------

float Time::time;
int Time::seconds;
int Time::minutes;
int Time::hours;

void Time::SetTime(int s_, int m_, int h_) {
	seconds = s_;
	minutes = m_;
	hours = h_;
}

void Time::Update(const float deltaTime) {
	time += deltaTime;

	if (time > 1.0f) {
		time = 0;
		seconds++;
	}

	if (seconds >= 60) {
		seconds = 0;
		minutes++;
	}

	if (minutes >= 60) {
		minutes = 0;
		hours++;
	}
}

void Time::Reset() {
	time = 0;
	seconds = 0;
	minutes = 0;
	hours = 0;
}

std::string Time::ToString() {
	std::string s, m;
	if (seconds < 10) {
		s = "0" + std::to_string(seconds);
	}
	else {
		s = std::to_string(seconds);
	}
	if (minutes < 10) {
		m = "0" + std::to_string(minutes);
	}
	else {
		m = std::to_string(minutes);
	}
	return std::to_string(hours) + ":" + m + ":" + s;
}