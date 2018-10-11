#include "UIEntities.h"
#include "Utilities.h"
#include "GameManager.h"
#include <iostream>

#include "Scene1.h"

//-------------------------------------------------- UI Button Entity --------------------------------------------------

//Constructors
UIButtonEntity::UIButtonEntity(int x_, int y_, int w_, int h_, std::string text_, TTF_Font* font_) {

	image = false;

	//Creating Components
	button = std::make_shared<UICanvasComponent>(w_, h_, *GameManager::assets.MakeColor(255, 255, 255));
	buttonLabel = std::make_shared<UILabelComponent>(text_, font_, *GameManager::assets.MakeColor(255, 255, 255));

	//Create Button Label Texture
	buttonLabel->CreateTexture(buttonLabel->Blended);

	//Assigning Positions
	button->SetPosition(x_, y_);
	buttonLabel->SetPosition(x_ + (w_ / 4) + buttonLabel->dimension.w / 4, y_ + (h_ / 4) + buttonLabel->dimension.h / 4);
	dimensions = {x_, y_, w_, h_};

	//Attaching Components to Entity
	this->AddComponent(button);
	this->AddComponent(buttonLabel);
}

UIButtonEntity::UIButtonEntity(int x_, int y_, int w_, int h_, std::string text_, TTF_Font* font_, std::string path_) {

	image = true;

	//Creating Components
	button = std::make_shared<UICanvasComponent>(w_, h_, path_);
	buttonLabel = std::make_shared<UILabelComponent>(text_, font_, *GameManager::assets.MakeColor(255, 255, 255));

	//Create Button Label Texture
	buttonLabel->CreateTexture(buttonLabel->Blended);

	//Assigning Positions
	button->SetPosition(x_, y_);
	buttonLabel->SetPosition(x_ + (w_ / 4) + buttonLabel->dimension.w / 4, y_ + (h_ / 4) + buttonLabel->dimension.h / 4);
	dimensions = { x_, y_, w_, h_ };

	//Attaching Components to Entity
	this->AddComponent(button);
	this->AddComponent(buttonLabel);
}

UIButtonEntity::~UIButtonEntity() { }

//Sets Color of a specific State
void UIButtonEntity::SetColor(int state, SDL_Color textColor_, SDL_Color bgColor_){
	auto it = colors.find(state);
	if (it != colors.end()){
		colors.find(state)->second[0] = textColor_;
		if(!image)
		colors.find(state)->second[1] = bgColor_;
	}
	else {
		colors[state].push_back(textColor_);
		if(!image)
		colors[state].push_back(bgColor_);
	}
}

void UIButtonEntity::SetColor(int state, SDL_Color textColor_) {
	auto it = colors.find(state);
	if (image) {
		if (it != colors.end()) {
			colors.find(state)->second[0] = textColor_;
		}
		else {
			colors[state].push_back(textColor_);
		}
	}
	else {
		std::cout << "Background Color was not included, setting default to white" << std::endl;
		SDL_Color white = *GameManager::assets.MakeColor(255, 255, 255);
		if (it != colors.end()) {
			colors.find(state)->second[0] = textColor_;
			colors.find(state)->second[1] = white;
		}
		else {
			colors[state].push_back(textColor_);
			colors[state].push_back(white);
		}
	}
}

void UIButtonEntity::SetImage(const std::string path_) {
	button->SetImage(path_);
}

void UIButtonEntity::Hover() {
	//Set Color of the Button Components
	buttonLabel->SetColor(colors.find(e_Hover)->second[0]);
	if(!image)
	button->SetColor(colors.find(e_Hover)->second[1]);

	//Insert Hover Code here...

}

void UIButtonEntity::MouseDown() {
	//Set Color of the Button Components
	buttonLabel->SetColor(colors.find(e_MouseDown)->second[0]);
	if (!image)
	button->SetColor(colors.find(e_MouseDown)->second[1]);


	//Insert MouseDown Code here...
	Scene1::text = "Button Pressed: " + buttonLabel->GetText();

	//Call Active Method if allowed 
	if (active) {
		Active();
	}
}

void UIButtonEntity::Active() {
	//Do Once Pattern
	if (!called) {
		called = true;

		//Set Color of the Button Components
		buttonLabel->SetColor(colors.find(e_Active)->second[0]);
		button->SetColor(colors.find(e_Active)->second[1]);

		//Insert Active Code Here...

	}
}

//Resets Active State
void UIButtonEntity::DeActivate() {
	called = false;
}

//Overidden: Updates the button
void UIButtonEntity::Update() {
	//Set Color of the Button Components
	buttonLabel->SetColor(colors.find(e_Normal)->second[0]);
	if(!image)
	button->SetColor(colors.find(e_Normal)->second[1]);

	//Checking where Mouse Position is relative to Button
	if (MouseController::x > dimensions.x && MouseController::y > dimensions.y && MouseController::x < dimensions.w + dimensions.x && MouseController::y < dimensions.h + dimensions.y) {
		Hover();
		if (MouseController::primaryButton) {
			MouseDown();
		}
	}

	//Create Button Label Texture
	buttonLabel->CreateTexture(buttonLabel->Blended);

	//Default Update
	for (auto c : components) { c->Update(); }
}

//------------------------------------------------------- UI Bar Entity --------------------------------------------------------

//Constructors
UIBarEntity::UIBarEntity(int x_, int y_, int w_, int h_, SDL_Color barColor_, bool isVertical_, bool flipped_, bool continuous_) {
	//Creates Components
	bar = std::make_shared<UICanvasComponent>(w_, h_, barColor_);

	//Sets the Bars Direction & Rotation
	isVertical = isVertical_;
	flipped = flipped_;
	continuous = continuous_;

	//Sets the Bar's Size & Position 
	barDimensions = { x_, y_, w_, h_ };
	barStartDimensions = barDimensions;
	bar->canvasDimension = barDimensions;
	
	//Attaches the component to the Entity
	this->AddComponent(bar);
}

UIBarEntity::UIBarEntity(int x_, int y_, int w_, int h_, SDL_Color barColor_, const std::string path_, bool isVertical_, bool flipped_, bool continuous_) {
	//Creates Components
	barOverlay = std::make_shared<UICanvasComponent>(w_, h_, path_);
	bar = std::make_shared<UICanvasComponent>(0, 0, barColor_);

	//Sets the Bars Direction & Rotation
	isVertical = isVertical_;
	flipped = flipped_;
	continuous = continuous_;

	//Sets the Bar's Size & Position 
	barDimensions = { x_ + 5, y_ + 5, w_ - 5, h_ - 5};
	barStartDimensions = barDimensions;
	bar->canvasDimension = barDimensions;

	//Attaches the component to the Entity
	this->AddComponent(bar);
	this->AddComponent(barOverlay);
}

UIBarEntity::~UIBarEntity() { }

//Changes the Bar by an amount
///NOTE: Values that can be chosen are -INF to -1, -0.5 to 0.5,  1 to INF
void UIBarEntity::Change(float amount) {
	if (fmodf(amount, 1) == 0 || accumulator >= 1.0f) {
		std::cout << amount << std::endl;
		if (amount < accumulator && !(amount < 0)) {
			amount = 1;
		}
		if (isVertical) {
			if (barDimensions.h > 0 && barDimensions.h + -amount < barStartDimensions.h) {
				barDimensions.h -= (int)amount;
				if (flipped) {
					barDimensions.y += (int)amount;
				}
			}
			else {
				//Insert Code Here Once Bar Reaches 0...

				Reset();//Resets Bar
			}
		}
		else {
			if (barDimensions.w > 0 && barDimensions.w + -amount < barStartDimensions.w) {
					barDimensions.w -= (int)amount;
				if (flipped) {
					barDimensions.x += (int)amount;
				}
			}
			else {
				//Insert Code Here Once Bar Reaches 0...

				Reset();//Resets bar
			}
		}
		accumulator = 0;
	}
	else {
		accumulator += amount;
	}
}

//Sets the rate of Reduction/Enlargment
void UIBarEntity::SetRate(float rate_) {
	rateOfReduction = rate_;
}

void UIBarEntity::SetFlags(bool isVertical_, bool flipped_, bool continuous_) {
	isVertical = isVertical_;
	flipped = flipped_;
	continuous = continuous_;
}

//Sets the Bars Dimensions
void UIBarEntity::SetBarDimensions(int x_, int y_, int w_, int h_) {
	barDimensions = { x_, y_, w_, h_ };
}

//Resets the bar to original Size & Position
void UIBarEntity::Reset() {
	barDimensions = barStartDimensions;
}

//Overidden: Updates the Bar
void UIBarEntity::Update() {
	//If Rate of change is Continuos, continue to reduce/increase bar
	if (continuous) { Change(rateOfReduction); }

	//Update the Bars Dimension
	bar->canvasDimension = barDimensions;

	std::cout << barDimensions.w << std::endl;

	//Default Update
	for (auto c : components) { c->Update(); }
}


