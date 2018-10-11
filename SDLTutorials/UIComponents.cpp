#include "ECS.h"
#include "UIComponents.h"
#include "GameManager.h"
#include <SDL_image.h>
#include "Utilities.h"

//Constructors
UILabelComponent::UILabelComponent(std::string text_, TTF_Font* font_, SDL_Color &color_) {
	SetPosition(0, 0);
	labelText = text_;
	font = font_;
	textColor = color_;
}

UILabelComponent::UILabelComponent(std::string text_, TTF_Font* font_, SDL_Color &color_, SDL_Color &backColor_) {
	SetPosition(0, 0);
	labelText = text_;
	font = font_;
	textColor = color_;
	backgroundColor = backColor_;
}

UILabelComponent::~UILabelComponent() { }

//Sets Position
void UILabelComponent::SetPosition(int x_, int y_) {
	dimension.x = x_;
	dimension.y = y_;
}

//Sets Label Text
void UILabelComponent::SetText(std::string text_) {
	labelText = text_;
}

//Sets Label's Text Color
void UILabelComponent::SetColor(SDL_Color &textColor_) {
	textColor = textColor_;
}

//Sets Label's Text & Background Color
void UILabelComponent::SetColor(SDL_Color &textColor_, SDL_Color &bgColor_) {
	textColor = textColor_;
	backgroundColor = bgColor_;
}

std::string UILabelComponent::GetText() {
	return labelText;
}

//Creates Texture From Text & Font
void UILabelComponent::CreateTexture(int type) {
	
	SDL_Surface* temp;//Creates temp surface

	//Chosing a Render Type
	switch (type) {
	case 0: temp = TTF_RenderText_Solid(font, labelText.c_str(), textColor);
		break;
	case 1: temp = TTF_RenderText_Shaded(font, labelText.c_str(), textColor, backgroundColor);
		break;
	default: temp = TTF_RenderText_Blended(font, labelText.c_str(), textColor);
		break;
	}

	//Creates Texture From Surface
	labelTexture = SDL_CreateTextureFromSurface(GameManager::renderer, temp);
	SDL_FreeSurface(temp);

	// Gets Width & Height of text
	SDL_QueryTexture(labelTexture, nullptr, nullptr, &dimension.w, &dimension.h);
}

//Overidden: Render Label
void UILabelComponent::Render() {
	SDL_RenderCopy(GameManager::renderer, labelTexture, nullptr, &dimension);
	SDL_DestroyTexture(labelTexture);
}

// --------------------------------------------- UI Canvas Component ------------------------------------------------------

//Constructors
UICanvasComponent::UICanvasComponent(int w_, int h_, SDL_Color &color_) {
	SetDimensions(0, 0, w_, h_);
	backgroundColor = color_;
	image = false;
}

UICanvasComponent::UICanvasComponent(int w_, int h_, const std::string path_) {
	SetDimensions(0, 0, w_, h_);
	canvasTexture = AssetManager::LoadTexture(path_.c_str(), GameManager::renderer);
	image = true;
}

UICanvasComponent::~UICanvasComponent() { SDL_DestroyTexture(canvasTexture); }

//Sets Color of Canvas
void UICanvasComponent::SetColor(SDL_Color &color_) {
	backgroundColor = color_;
	image = false;
}

//Sets Image of Canvas
void UICanvasComponent::SetImage(const std::string path_) {
	canvasTexture = AssetManager::LoadTexture(path_.c_str(), GameManager::renderer);
	image = true;
}

//Sets Position of Canvas 
void UICanvasComponent::SetPosition(int x_, int y_) {
	canvasDimension.x = x_;
	canvasDimension.y = y_;
}

//Sets the Dimensions of the Canvas
void UICanvasComponent::SetDimensions(int x_, int y_, int w_, int h_) {
	canvasDimension.x = x_;
	canvasDimension.y = y_;
	canvasDimension.w = w_;
	canvasDimension.h = h_;
}

//Overidden: Renders Canvas/Image
void UICanvasComponent::Render() {
	if (image) {
		SDL_RenderCopy(GameManager::renderer, canvasTexture, nullptr, &canvasDimension);
	}
	else {
		SDL_SetRenderDrawColor(GameManager::renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		SDL_RenderFillRect(GameManager::renderer, &canvasDimension);
	}
}
