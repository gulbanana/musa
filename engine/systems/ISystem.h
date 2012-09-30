#pragma once
#include <memory>
#include <vector>
#include <string>
#include <typeinfo>
#include <SDL_events.h>
#include "../entities/IEntity.h"

enum class SyID
{
    Control,
    Collision,
    Input,
    Display,
    Motion,
    Physics,
    Render,
    UI
};

class ISystem : public Identifiable<SyID>
{
public:
	virtual ~ISystem() {}
	void frame();
	bool event(SDL_Event& event) { return on_event(event); };	//for later interface changes

//an ISystem implementation can register which components to maintainin in its entity list
protected:
	std::vector<std::weak_ptr<IEntity>> entities;
public:
	virtual std::vector<IComponent::ID> required_components() { return std::vector<IComponent::ID>(); }
	virtual void add_entity(std::weak_ptr<IEntity> new_entity);

//Systems can also optionally process frames, entity updates, or SDL events
private:
	virtual void on_frame() {}
	virtual void on_post_frame() {}
	virtual void on_entity(std::shared_ptr<IEntity> entity) {}
	virtual bool on_event(SDL_Event& event) { return false; }	//true = handled
};

