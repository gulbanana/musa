#pragma once
#include <memory>
#include <vector>
#include <SDL_events.h>
#include "IEntity.h"

enum class SYS
{
    Collision,
	Control,
    Input,
    Logic,
    Motion,
    Physics,
    Render,
    UI
};

class ISystem : public Identifiable<SYS>
{
public:
	virtual ~ISystem() {}
	void frame();
	bool event(SDL_Event& event);

//an ISystem implementation registers required components and other system dependencies
public:
	virtual std::vector<ISystem::ID> required_systems() const;
	virtual std::vector<IComponent::ID> required_components() const;

//system dependencies are used for ordering
	bool operator<(ISystem const& rhs);

//the base ISystem maintains an entity list
protected:
	std::vector<std::weak_ptr<IEntity>> entities;
public:
	virtual void add_entity(std::weak_ptr<IEntity> new_entity);

//Systems can optionally process frames, entity updates, or SDL events
private:
	virtual void on_frame() {}
	virtual void on_post_frame() {}
	virtual void on_entity(std::shared_ptr<IEntity> entity) {}
	virtual bool on_event(SDL_Event& event) { return false; }	//true = handled
};

