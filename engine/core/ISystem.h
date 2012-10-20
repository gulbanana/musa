#pragma once
#include <SDL_events.h>
#include "IEntity.h"

enum class SYS
{
    Collision,
	Control,
	Logic,
    Motion,
    Render,
    UI,
	Last = UI
};

class ISystem : public Identifiable<SYS>
{
public:
	//Systems can optionally process frames or SDL events
	virtual ~ISystem() {}
	virtual void on_frame() = 0;
	virtual void on_message() = 0;
	virtual bool on_event(SDL_Event& event) = 0;

	//an ISystem implementation registers required components; the game engine supplies entities meeting the specification
	virtual std::vector<IComponent::ID> required_components() const = 0;
	virtual void add_entity(std::weak_ptr<IEntity> new_entity) = 0;

	//system dependencies are used for ordering
	virtual std::vector<ISystem::ID> required_systems() const = 0;
};