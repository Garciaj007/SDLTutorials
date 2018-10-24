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

	std::shared_ptr<System> system1, system2;

public:
	static std::string text;
	static int w, h;

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
