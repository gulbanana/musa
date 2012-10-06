#pragma once
#include <memory>
#include <vector>
#include <SDL_events.h>
#include "IEntity.h"

enum class SYS
{
    Collision,
	Control,
	Logic,
    Motion,
    Render,
    UI
};

class ISystem : public Identifiable<SYS>
{
public:
	//Systems can optionally process frames or SDL events
	virtual ~ISystem() {}
	virtual void on_frame() {}
	virtual bool on_event(SDL_Event& event) { return false; }

public:
	//an ISystem implementation registers required components; the game engine supplies entities meeting the specification
	virtual std::vector<IComponent::ID> required_components() const { return std::vector<IComponent::ID>(); }
	virtual void add_entity(std::weak_ptr<IEntity> new_entity) {}

	//system dependencies are used for ordering
	virtual std::vector<ISystem::ID> required_systems() const { return std::vector<ISystem::ID>(); }
};