#ifndef UICOMPONENTS_H
#define UICOMPONENTS_H

#include "ECS.h"
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <memory>

//--------------------------------------------- UI Label Component -----------------------------------------------------

class UILabelComponent : public Component {
private:
	//Members
	std::string labelText;
	SDL_Color textColor, backgroundColor;
	TTF_Font* font;
	SDL_Texture* labelTexture;
public:
	//Size and position of Label
	SDL_Rect dimension;

	//Const Text Rendering Types
	static enum TextRenderType {Solid = 0, Shaded, Blended} type;

	//Constructors
	UILabelComponent(std::string text_, TTF_Font* font_, SDL_Color &color_);
	UILabelComponent(std::string text_, TTF_Font* font_, SDL_Color &color_, SDL_Color &backColor_);
	~UILabelComponent();

	//MemberMethods
	void SetPosition(int x_, int y_);
	void SetText(std::string text_);
	void SetColor(SDL_Color &textColor_);
	void SetColor(SDL_Color &textColor_, SDL_Color &bgColor_);
	std::string GetText();
	void CreateTexture(int type);

	//Overidden Methods
	void Render() override;
};

//------------------------------------------------- UI Canvas Component ----------------------------------------------

class UICanvasComponent : public Component {
private:
	//Members
	SDL_Color backgroundColor;
	SDL_Texture* canvasTexture;

public: 
	bool image; ///If Image or Solid Color
	//Size and position of Canvas
	SDL_Rect canvasDimension;

	//Constructor
	UICanvasComponent(int w_, int h_, SDL_Color &color_);
	UICanvasComponent(int w_, int h_, const std::string path_);
	~UICanvasComponent();

	//Member Methods
	void SetColor(SDL_Color &color);
	void SetImage(const std::string path_);
	void SetPosition(int x_, int y_);
	void SetDimensions(int x_, int y_, int w_, int h_);

	//Overidden Methods
	void Render() override;
};


#endif // !UICOMPONENTS_H

