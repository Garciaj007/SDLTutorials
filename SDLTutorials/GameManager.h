#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <SDL/SDL.h>
#include "Scene.h"
#include "Utilities.h"
#include <memory>
#include "Window.h"
#include "Timer.h"

class GameManager {
private:
	//Members
	std::unique_ptr<Window> windowPtr;
	std::unique_ptr<Timer> timer;
	
	bool isRunning;///If Game is running
	std::unique_ptr<Scene> currentScene;///Curent Scene Attached
public:
	//Defining Static members 
	static AssetManager assets;
	static SDL_Renderer* renderer;

	//Events & Input
	SDL_Event event;

	//Constructor
	GameManager();
	~GameManager();

	//Member Methods
	bool OnCreate();
	void OnDestroy();
	void Run();
};
#endif
