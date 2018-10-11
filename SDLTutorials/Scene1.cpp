#include "Scene1.h"
#include <iostream>
#include "Components.h"
#include "Utilities.h"
#include "GameManager.h"

std::string Scene1::text = "This is a Label";

//Constructors
Scene1::Scene1(SDL_Window* window_)
{
	window = window_;
}

Scene1::~Scene1() { }

//When Scene is Created
bool Scene1::OnCreate() {

	//Creates scene and allows for changes in Update or render
	system1.Create();

	//Resetting Time
	Time::Reset();

	//Color Palette
	SDL_Color lightGreen = { 138, 176, 171 };
	SDL_Color slateBlue = { 62, 80, 91 };
	SDL_Color evergreen = { 38, 65, 60 };
	SDL_Color darkGrey = { 26, 29, 26 };
	SDL_Color black = { 3, 18, 14 };
	SDL_Color white = { 230, 255, 250 };

	//Create Simple Entities & Attach to system
	backgroundCanvasEntity = system1.CreateEntity();
	spriteEntity = system1.CreateEntity();
	labelEntity = system1.CreateEntity();
	timeLabelEntity = system1.CreateEntity();

	s2_backgroundCanvasEntity = system2.CreateEntity();
	s2_labelEntity = system2.CreateEntity();
	
	//Emplacing Item names
	items.push_back("Banana");
	items.push_back("Boat");
	items.push_back("Chicken");
	items.push_back("Crystal");
	items.push_back("Fish");
	items.push_back("Pickaxe");
	items.push_back("Shovel");
	items.push_back("Water");

	//Create Complex Entities
	for (int i = 0; i < 8; i++) {
		itemButtons.emplace_back(std::make_shared<UIButtonEntity>((150 * i) + 50, 600, 125, 50, items[i], GameManager::assets.GetFont("Bahnschrift_14"), "Assets/" + items[i] + ".png"));
		s2_itemButtons.emplace_back(std::make_shared<UIButtonEntity>((150 * i) + 50, 600, 125, 50, "Btn " + std::to_string(i), GameManager::assets.GetFont("Bahnschrift_14")));
	}
	barEntity = std::make_shared<UIBarEntity>(600, 200, 400, 50, evergreen, false, false, true);
	s2_BarEntity = std::make_shared<UIBarEntity>(600, 200, 400, 50, evergreen, false, false, false);

	//Attaches Complex Entities to system
	for (int i = 0; i < 8; i++) {
		system1.AddEntity(itemButtons[i]);
		system2.AddEntity(s2_itemButtons[i]);
	}
	system1.AddEntity(barEntity);
	system2.AddEntity(s2_BarEntity);

	//Sets Bar Rate Of Decrease
	barEntity->SetRate(1.0f);
	
	//Setting Button Color States 
	for (int i = 0; i < 8; i++) {
		itemButtons[i]->SetColor(itemButtons[i]->e_Normal, white);
		s2_itemButtons[i]->SetColor(s2_itemButtons[i]->e_Normal, black, slateBlue);
		itemButtons[i]->SetColor(itemButtons[i]->e_Hover, evergreen);
		s2_itemButtons[i]->SetColor(s2_itemButtons[i]->e_Hover, darkGrey, lightGreen);
		itemButtons[i]->SetColor(itemButtons[i]->e_MouseDown, black);
		s2_itemButtons[i]->SetColor(s2_itemButtons[i]->e_MouseDown, white, evergreen);
		itemButtons[i]->SetColor(itemButtons[i]->e_Active, white);
		s2_itemButtons[i]->SetColor(s2_itemButtons[i]->e_Active, white, black);
	}
	
	//Getting window Size
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	//Creating Components
	spriteComponent = std::make_shared<UICanvasComponent>(200, 80, "Assets/Boat.png");
	masterCanvasComponent = std::make_shared<UICanvasComponent>(w, h, darkGrey);
	masterLabelComponent = std::make_shared<UILabelComponent>("This is a label", GameManager::assets.GetFont("Bahnschrift_20"), white);
	timeLabelComponent = std::make_shared<UILabelComponent>("0:00:00", GameManager::assets.GetFont("Bahnschrift_40"), white, lightGreen);

	s2_masterCanvasComponent = std::make_shared<UICanvasComponent>(w, h, slateBlue);
	s2_labelComponent = std::make_shared<UILabelComponent>("System 2 Displayed", GameManager::assets.GetFont("Bahnschrift_40"), darkGrey);

	//Setting Component Dimensions
	masterLabelComponent->SetPosition(150, 300);
	masterLabelComponent->CreateTexture(masterLabelComponent->Blended);
	timeLabelComponent->SetPosition(950, 100);
	timeLabelComponent->CreateTexture(timeLabelComponent->Shaded);
	spriteComponent->SetPosition(100, 100);

	s2_labelComponent->SetPosition(200, 200);
	s2_labelComponent->CreateTexture(s2_labelComponent->Blended);

	//Attaching Components to Entities
	backgroundCanvasEntity->AddComponent(masterCanvasComponent);
	labelEntity->AddComponent(masterLabelComponent);
	timeLabelEntity->AddComponent(timeLabelComponent);
	spriteEntity->AddComponent(spriteComponent);

	s2_backgroundCanvasEntity->AddComponent(s2_masterCanvasComponent);
	s2_labelEntity->AddComponent(s2_labelComponent);

	return true;
}

//When Scene is Destroyed
void Scene1::OnDestroy() { }

//When Scene is Updated
void Scene1::Update(const float time_) {

	//Update Time;
	Time::Update(time_);

	if (system1.IsActive()) {
		//Setting & Rendering Text
		masterLabelComponent->SetText(text);
		masterLabelComponent->CreateTexture(masterLabelComponent->Blended);
		timeLabelComponent->SetText(Time::ToString());
		timeLabelComponent->CreateTexture(timeLabelComponent->Shaded);

		//Updates the system
		system1.Update();
	}
	else if (system2.IsActive()) {
		s2_labelComponent->CreateTexture(s2_labelComponent->Blended);

		system2.Update();
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
			system2.Destroy();
			//system2.Refresh();
			system1.Create();
		} 
		if (e.key.keysym.scancode == SDL_SCANCODE_F2) {
			system1.Destroy();
			//system1.Refresh();
			system2.Create();
		}
		if (e.key.keysym.scancode == SDL_SCANCODE_LEFT) {
			s2_BarEntity->Change(10);
		}
		if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
			s2_BarEntity->Change(-10);
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
	if (system1.IsActive()) {
		system1.Render();
	}
	else if (system2.IsActive()) {
		system2.Render();
	}
		

	//Updates the screen with any rendering performed since the previous call
	SDL_RenderPresent(GameManager::renderer);
}