#include "Scene1.h"
#include <iostream>
#include "Utilities.h"
#include "GameManager.h"
#include "UIManager.h"

std::string Scene1::text = "This is a Label";
int Scene1::w = 0;
int Scene1::h = 0;

//Constructors
Scene1::Scene1(SDL_Window* window_)
{
	window = window_;

	system1 = std::make_shared<UISystem1>();
	system2 = std::make_shared<UISystem2>();
}

Scene1::~Scene1() { }

//When Scene is Created
bool Scene1::OnCreate() {

	SDL_GetWindowSize(window, &w, &h);

	//Creates scene and allows for changes in Update or render
	system1->Create();

	//Resetting Time
	Time::Reset();
	return true;
}

//When Scene is Destroyed
void Scene1::OnDestroy() { }

//When Scene is Updated
void Scene1::Update(const float time_) {
	//Update Time;
	Time::Update(time_);

	if (system1->IsActive()) {
		system1->Update();
	}
	else if (system2->IsActive()) {
		system2->Update();
	}
}

//Scene Handles Events
void Scene1::HandleEvents(const SDL_Event &e) {
	switch (e.type) {
		//If Mouse is Down
	case SDL_MOUSEBUTTONDOWN:
		if (e.button.button == SDL_BUTTON_LEFT) {
			MouseController::primaryButton = true;
		}
		else if (e.button.button == SDL_BUTTON_RIGHT) {
			MouseController::secondaryButton = true;
		}
		break;
		//If Mouse is Up
	case SDL_MOUSEBUTTONUP:
		MouseController::primaryButton = false;
		MouseController::secondaryButton = false;
		//If Mouse is Double Clicked
		if (e.button.clicks == 2) {
			MouseController::doubleClicks = true;
		}
		break;
		//When Mouse Moves
	case SDL_MOUSEMOTION:
		MouseController::doubleClicks = false;
		MouseController::x = e.motion.x;
		MouseController::y = e.motion.y;
		break;
	case SDL_KEYDOWN:
		if (e.key.keysym.scancode == SDL_SCANCODE_F1) {
			system2->Destroy();
			system2->Refresh();
			system1->Create();
		} 
		if (e.key.keysym.scancode == SDL_SCANCODE_F2) {
			system1->Destroy();
			system1->Refresh();
			system2->Create();
		}
		if (e.key.keysym.scancode == SDL_SCANCODE_LEFT) {
			//s2_BarEntity->Change(10);
		}
		if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
			//s2_BarEntity->Change(-10);
		}
	}
}

//Renders Scene
void Scene1::Render() {
	//Clears the renderer
	SDL_RenderClear(GameManager::renderer);
	//Sets color to transparent
	SDL_SetRenderDrawColor(GameManager::renderer, 0, 0, 0, 0);
	//Draws Transparent Rect as Background
	SDL_RenderFillRect(GameManager::renderer, nullptr);

	//Renders all entities in system
	if (system1->IsActive()) {
		system1->Render();
	}
	else if (system2->IsActive()) {
		system2->Render();
	}
		
	//Updates the screen with any rendering performed since the previous call
	SDL_RenderPresent(GameManager::renderer);
}