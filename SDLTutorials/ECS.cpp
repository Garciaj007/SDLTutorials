#include "ECS.h"
//---------------------------------------------- Entity ----------------------------------------------------------

//Adds a Component to an Entity
void Entity::AddComponent(std::shared_ptr<Component> component) {
	components.emplace_back(component);
	component->Create();
}

//Updates Components
void Entity::Update() {
	for (auto c : components) { c->Update(); }
}

//Renders Components
void Entity::Render() { 
	for (auto c : components) { c->Render(); }
}

//---------------------------------------------  System  ---------------------------------------------------------

//Creates A Basic Entity & Attaches to System
std::shared_ptr<Entity> System::CreateEntity() {
	std::shared_ptr<Entity> e = std::make_shared<Entity>();
	system.emplace_back(e);
	return e;
}

//Allows Attachment of Complex Entities
void System::AddEntity(std::shared_ptr<Entity> e) {
	system.emplace_back(e);
}

//Updates Entities
void System::Update() {
	for (auto e : system) { e->Update(); }
}

//Renders Entities
void System::Render() {
	for (auto e : system) { e->Render(); }
}

//Removes Destroyed Entities
void System::Refresh() {
	system.erase(std::remove_if(system.begin(), system.end(), [](std::shared_ptr<Entity> const &e) { return !e->IsActive(); }), system.end());
}

//Destroys Entities
void System::Destroy() {
	for (auto e : system) { e->Destroy(); }
}