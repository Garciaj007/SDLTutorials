#ifndef WINDOW_H
#define WINDOW_H
#include <SDL/SDL.h>
class Window {
private:
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Point size;
	SDL_Point position;
	const char* name;
public:
	Window(const char* name_, SDL_Point size_, SDL_Point position_);
	~Window();
	bool OnCreate();
	void OnDestroy();
	SDL_Window* GetSDL_Window();
};
#endif // !WINDOW_H