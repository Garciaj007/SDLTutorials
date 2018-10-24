#include "UIManager.h"
#include "ECS.h"
#include "GameManager.h"
#include "Utilities.h"
#include "Scene1.h"

void UISystem1::Create() {
	active = true;

	//Color Palette
	SDL_Color lightGreen = { 138, 176, 171 };
	SDL_Color slateBlue = { 62, 80, 91 };
	SDL_Color evergreen = { 38, 65, 60 };
	SDL_Color darkGrey = { 26, 29, 26 };
	SDL_Color black = { 3, 18, 14 };
	SDL_Color white = { 230, 255, 250 };

	backgroundCanvasEntity = CreateEntity();
	spriteEntity = CreateEntity();
	labelEntity = CreateEntity();
	timeLabelEntity = CreateEntity();

	//Emplacing Item names
	items.push_back("Banana");
	items.push_back("Boat");
	items.push_back("Chicken");
	items.push_back("Crystal");
	items.push_back("Fish");
	items.push_back("Pickaxe");
	items.push_back("Shovel");
	items.push_back("Water");

	for (int i = 0; i < 8; i++) {
		itemButtons.emplace_back(std::make_shared<UIButtonEntity>((150 * i) + 50, 600, 125, 50, items[i], GameManager::assets.GetFont("Bahnschrift_14"), "Assets/" + items[i] + ".png"));
	}

	barEntity = std::make_shared<UIBarEntity>(600, 200, 400, 50, evergreen, false, false, true);

	//Attaches Complex Entities to system
	for (int i = 0; i < 8; i++) {
		AddEntity(itemButtons[i]);
	}

	AddEntity(barEntity);

	//Setting Button Color States 
	for (int i = 0; i < 8; i++) {
		itemButtons[i]->SetColor(itemButtons[i]->e_Normal, white);
		itemButtons[i]->SetColor(itemButtons[i]->e_Hover, evergreen);
		itemButtons[i]->SetColor(itemButtons[i]->e_MouseDown, black);
		itemButtons[i]->SetColor(itemButtons[i]->e_Active, white);
	}

	//Creating Components
	spriteComponent = std::make_shared<UICanvasComponent>(200, 80, "Assets/Boat.png");
	masterCanvasComponent = std::make_shared<UICanvasComponent>(Scene1::w, Scene1::h, darkGrey);
	masterLabelComponent = std::make_shared<UILabelComponent>("This is a label", GameManager::assets.GetFont("Bahnschrift_20"), white);
	timeLabelComponent = std::make_shared<UILabelComponent>("0:00:00", GameManager::assets.GetFont("Bahnschrift_40"), white, lightGreen);

	//Setting Component Dimensions
	masterLabelComponent->SetPosition(150, 300);
	masterLabelComponent->CreateTexture(masterLabelComponent->Blended);
	timeLabelComponent->SetPosition(950, 100);
	timeLabelComponent->CreateTexture(timeLabelComponent->Shaded);
	spriteComponent->SetPosition(100, 100);

	//Attaching Components to Entities
	backgroundCanvasEntity->AddComponent(masterCanvasComponent);
	labelEntity->AddComponent(masterLabelComponent);
	timeLabelEntity->AddComponent(timeLabelComponent);
	spriteEntity->AddComponent(spriteComponent);

	for (auto e : system){ e->Create(); }
	
}

void UISystem1::Update() {
	//Setting & Rendering Text
	masterLabelComponent->SetText(Scene1::text);
	masterLabelComponent->CreateTexture(masterLabelComponent->Blended);
	timeLabelComponent->SetText(Time::ToString());
	timeLabelComponent->CreateTexture(timeLabelComponent->Shaded);

	for (auto e : system) { e->Update(); }
}

void UISystem2::Create() {

	//Color Palette
	SDL_Color lightGreen = { 138, 176, 171 };
	SDL_Color slateBlue = { 62, 80, 91 };
	SDL_Color evergreen = { 38, 65, 60 };
	SDL_Color darkGrey = { 26, 29, 26 };
	SDL_Color black = { 3, 18, 14 };
	SDL_Color white = { 230, 255, 250 };

	s2_backgroundCanvasEntity = CreateEntity();
	s2_labelEntity = CreateEntity();

	for (int i = 0; i < 8; i++) {
		s2_itemButtons.emplace_back(std::make_shared<UIButtonEntity>((150 * i) + 50, 600, 125, 50, "Btn " + std::to_string(i), GameManager::assets.GetFont("Bahnschrift_14")));
	}

	s2_BarEntity = std::make_shared<UIBarEntity>(600, 200, 400, 50, evergreen, false, false, false);

	//Attaches Complex Entities to system
	for (int i = 0; i < 8; i++) {
		AddEntity(s2_itemButtons[i]);
	}

	AddEntity(s2_BarEntity);

	//Setting Button Color States 
	for (int i = 0; i < 8; i++) {
		s2_itemButtons[i]->SetColor(s2_itemButtons[i]->e_Normal, black, slateBlue);
		s2_itemButtons[i]->SetColor(s2_itemButtons[i]->e_Hover, darkGrey, lightGreen);
		s2_itemButtons[i]->SetColor(s2_itemButtons[i]->e_MouseDown, white, evergreen);
		s2_itemButtons[i]->SetColor(s2_itemButtons[i]->e_Active, white, black);
	}

	s2_masterCanvasComponent = std::make_shared<UICanvasComponent>(Scene1::w, Scene1::h, slateBlue);
	s2_labelComponent = std::make_shared<UILabelComponent>("System 2 Displayed", GameManager::assets.GetFont("Bahnschrift_40"), darkGrey);

	s2_labelComponent->SetPosition(200, 200);
	s2_labelComponent->CreateTexture(s2_labelComponent->Blended);

	s2_backgroundCanvasEntity->AddComponent(s2_masterCanvasComponent);
	s2_labelEntity->AddComponent(s2_labelComponent);
}

void UISystem2::Update() {
	s2_labelComponent->CreateTexture(s2_labelComponent->Blended);
	for (auto e : system) { e->Update(); }
}