#ifndef ECS_H
#define ECS_H
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

//----------------------------------------------------- Component ------------------------------------------------------
///struct was made just to structure Components to entities
struct Component {
	//Virtual Functions that dont have to be implemented
	virtual void Create() { }; //Used to Create
	virtual void Update() { }; //Used to Update
	virtual void Render() { }; //Used to Render
};

//------------------------------------------------------- Entity --------------------------------------------------------

class Entity {
protected:
	//Whether the Entity is active or not
	bool active = true;
	//A vector of Components
	std::vector<std::shared_ptr<Component>> components;
public:
	// Virtual Functions 
	virtual void Update();
	virtual void Render();

	//Member Functions
	void AddComponent(std::shared_ptr<Component> component);
	inline bool IsActive() const { return active; }
	inline bool HasComponents() const { return !components.empty(); }
	inline void Destroy() { active = false; }
};

//-------------------------------------------------------- System -------------------------------------------------------

class System {
private :
	//A vector of Entities
	std::vector<std::shared_ptr<Entity>> system;
public:
	//Member Functions
	std::shared_ptr<Entity> CreateEntity(); ///Creates a Basic Entity
	void AddEntity(std::shared_ptr<Entity> entity); //Allows Insertion for a complex Entity
	void Update();
	void Render();
	void Refresh();
	void Destroy();
};
#endif
