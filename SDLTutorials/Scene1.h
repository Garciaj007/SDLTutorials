#ifndef SCENE1_H
#define SCENE1_H

#include "Scene.h"
#include <memory>
#include "ECS.h"
#include "Components.h"
#include "UIComponents.h"
#include "UIEntities.h"
#include <vector>
class Scene1 : public Scene
{
private:
	//Members
	SDL_Window* window;
	System scene1System;

	//Entities
	std::shared_ptr<Entity> backgroundCanvasEntity;
	std::shared_ptr<Entity> timeLabelEntity;
	std::shared_ptr<Entity> labelEntity;
	std::vector<std::shared_ptr<UIButtonEntity>> itemButtons;
	std::vector<std::string> items;
	std::shared_ptr<UIBarEntity> barEntity;

	//Components
	std::shared_ptr<UICanvasComponent> masterCanvasComponent;
	std::shared_ptr<UILabelComponent> masterLabelComponent;
	std::shared_ptr<UILabelComponent> timeLabelComponent;
public:
	static std::string text;

	//Constructor
	Scene1(SDL_Window* window_);
	~Scene1();

	//Member Methods
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void HandleEvents(const SDL_Event &e);
	void Render();
};
#endif
