#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include <iostream>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "Scene1.h"

//Declaring Static Members
AssetManager GameManager::assets; /// An instance of the AssetManager class
SDL_Renderer* GameManager::renderer; ///An instance of the SDL_Renderer

//Constructor
GameManager::GameManager() {
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
}

// When Game is created
bool GameManager::OnCreate() {
	//Dimensions of Window
	const SDL_Point SCREENSIZE {1280, 720}; 
	const SDL_Point SCREENPOS{ SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED };
	
	//Creating 
	windowPtr = std::make_unique<Window>("SDL Game 1", SCREENSIZE, SCREENPOS);

	//Default Check Statements

	//Check if Window ptr was Sucessful
	if (windowPtr == nullptr) {
		OnDestroy();
		return false;
	}

	//Check if Window Creation was Sucessful
	if (windowPtr->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	//Add Fonts Here
	assets.AddFont("Bahnschrift_14", "Assets/Fonts/bahnschrift.ttf", 14);
	assets.AddFont("Bahnschrift_20", "Assets/Fonts/bahnschrift.ttf", 20);
	assets.AddFont("Bahnschrift_40", "Assets/Fonts/bahnschrift.ttf", 40);

	//Create Renderer
	renderer = SDL_CreateRenderer(windowPtr->GetSDL_Window(), -1, 0);

	//Check if Render ptr was Sucessful
	if (renderer == nullptr) {
		OnDestroy();
		return false;
	}

	//Check if Timer ptr was Sucessful
	timer = std::make_unique<Timer>();
	if (timer == nullptr) {
		OnDestroy();
		return false;
	}
	
	//Check if ptr was Sucessful
	currentScene = std::make_unique<Scene1>(windowPtr->GetSDL_Window());
	if (currentScene == nullptr) {
		OnDestroy();
		return false;
	}
	
	//Check if Scene Creation was Sucessful
	if (currentScene->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	return true;
}

/// Here's the whole game
void GameManager::Run() {
	timer->Start();
	while (isRunning) {
		if (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT: isRunning = false;
				break;
			}
			currentScene->HandleEvents(event);
		}

		timer->UpdateFrameTicks();
		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();

		/// Keeep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec
	}
}

GameManager::~GameManager() {}

void GameManager::OnDestroy() {
	assets.CloseFonts();
	SDL_DestroyRenderer(renderer);
}