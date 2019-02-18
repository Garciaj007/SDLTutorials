#include "Window.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <iostream>

Window::Window(const char* name_, SDL_Point size_, SDL_Point position_) {
	screenSurface = nullptr;
	window = nullptr;
	size = size_;
	position = position_;
	name = name_;
}

bool Window::OnCreate() {
	//Check if libraries are functioning conrrectly...
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		std::cout << "IMG_ERROR: " << IMG_GetError() << std::endl;
		return false;
	}

	if (TTF_Init() < 0) {
		std::cout << "TTF_ERROR: " << TTF_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow(name, position.x, position.y, size.x, size.y, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	screenSurface = SDL_GetWindowSurface(window);
	if (screenSurface == nullptr) {
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

void Window::OnDestroy() {
	/// Kill the surface first
	if (screenSurface) {
		SDL_FreeSurface(screenSurface);
	}

	/// Now kill the window
	if (window) {
		SDL_DestroyWindow(window);
	}

	///Exit the SDL subsystems
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

Window::~Window() {}

SDL_Window* Window::GetSDL_Window() {
	return window;
}