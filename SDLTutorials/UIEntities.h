#ifndef UIENTITIES_H
#define UIENTITIES_H
#include "ECS.h"
#include "UIComponents.h"
#include <SDL.h>
#include <map>
#include <vector>
#include <string>

//------------------------------------------------ UI Button Entity --------------------------------------------------

class UIButtonEntity : public Entity {
private:
	//Components
	std::shared_ptr<UICanvasComponent> button;
	std::shared_ptr<UILabelComponent> buttonLabel;

	//Containers
	std::map<int, std::vector<SDL_Color>> colors;

	//Members
	SDL_Rect dimensions;
	bool called = false;
public:
	// This allows button toggle
	bool active = false; 

	//Const Button States
	static enum States { e_Normal = 0, e_Hover, e_MouseDown, e_Active } states;

	//Constructor
	UIButtonEntity(int x_, int y_, int w_, int h_, const std::string text_, TTF_Font* font_);
	~UIButtonEntity();

	//Member Methods
	void SetColor(int state, SDL_Color textColor_, SDL_Color backgroundColor_);
	void SetImage(const std::string path_);
	void Hover();
	void MouseDown();
	void Active();
	void DeActivate();

	//Overidden Methods
	void Update() override;
};

//------------------------------------------------ UI Bar Entity --------------------------------------------------

class UIBarEntity : public Entity {
private:
	//Components
	std::shared_ptr<UICanvasComponent> bar;
	std::shared_ptr<UICanvasComponent> barOverlay;

	//Size & position of bar, Starting & Continuos
	SDL_Rect barDimensions;
	SDL_Rect barStartDimensions;

	//Direction, Horizontal/Vertical, +/- Rate of Change, Continuos Rate...
	bool isVertical, flipped, continuous;

	//Speed at which bar Reduces
	float rateOfReduction = 1.0f;
	float accumulator = 0;
public:
	//Constructor
	UIBarEntity(int x_, int y_, int w_, int h_, SDL_Color barColor_, bool isVertical_, bool flipped_, bool continuous_j);
	UIBarEntity(int x_, int y_, int w_, int h_, SDL_Color barColor_, const std::string path_, bool isVertical_, bool flipped_, bool continous_);
	~UIBarEntity();

	//Member Functions
	void Change(float amount_);
	void SetRate(float rate_);
	void SetFlags(bool isVertical_, bool flipped_, bool continuous_);
	void SetBarDimensions(int x_, int y_, int w_, int h_);
	void Reset();

	//Overidden Methods
	void Update() override;
};

#endif

