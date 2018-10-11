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
	System system1, system2;

	std::vector<std::string> items;

	//System 1 Entities
	std::shared_ptr<Entity> backgroundCanvasEntity;
	std::shared_ptr<Entity> timeLabelEntity;
	std::shared_ptr<Entity> labelEntity;
	std::shared_ptr<Entity> spriteEntity;
	std::vector<std::shared_ptr<UIButtonEntity>> itemButtons;
	std::shared_ptr<UIBarEntity> barEntity;

	//System 2 Entities
	std::shared_ptr<Entity> s2_backgroundCanvasEntity;
	std::shared_ptr<Entity> s2_labelEntity;
	std::vector<std::shared_ptr<UIButtonEntity>> s2_itemButtons;
	std::shared_ptr<UIBarEntity> s2_BarEntity;

	//System 1 Components
	std::shared_ptr<UICanvasComponent> masterCanvasComponent;
	std::shared_ptr<UILabelComponent> masterLabelComponent;
	std::shared_ptr<UILabelComponent> timeLabelComponent;
	std::shared_ptr<UICanvasComponent> spriteComponent;

	//System 2 Components
	std::shared_ptr<UICanvasComponent> s2_masterCanvasComponent;
	std::shared_ptr<UILabelComponent> s2_labelComponent;

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
