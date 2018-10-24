#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "ECS.h"
#include "UIEntities.h"

class UISystem1 : public System {

	//System 1 Entities
	std::shared_ptr<Entity> backgroundCanvasEntity;
	std::shared_ptr<Entity> timeLabelEntity;
	std::shared_ptr<Entity> labelEntity;
	std::shared_ptr<Entity> spriteEntity;
	std::vector<std::shared_ptr<UIButtonEntity>> itemButtons;
	std::shared_ptr<UIBarEntity> barEntity;

	//System 1 Components
	std::shared_ptr<UICanvasComponent> masterCanvasComponent;
	std::shared_ptr<UILabelComponent> masterLabelComponent;
	std::shared_ptr<UILabelComponent> timeLabelComponent;
	std::shared_ptr<UICanvasComponent> spriteComponent;

	std::vector<std::string> items;

	void Create() override;
	void Update() override;
};

class UISystem2 : public System {

	//System 2 Entities
	std::shared_ptr<Entity> s2_backgroundCanvasEntity;
	std::shared_ptr<Entity> s2_labelEntity;
	std::vector<std::shared_ptr<UIButtonEntity>> s2_itemButtons;
	std::shared_ptr<UIBarEntity> s2_BarEntity;

	//System 2 Components
	std::shared_ptr<UICanvasComponent> s2_masterCanvasComponent;
	std::shared_ptr<UILabelComponent> s2_labelComponent;

	void Create() override;
	void Update() override;
};

#endif

