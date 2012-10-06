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
	virtual ~ISystem() = 0;
	virtual void on_frame();
	virtual bool on_event(SDL_Event& event);

public:
	//an ISystem implementation registers required components; the game engine supplies entities meeting the specification
	virtual std::vector<IComponent::ID> required_components() const;
	virtual void add_entity(std::weak_ptr<IEntity> new_entity);

	//system dependencies are used for ordering
	virtual std::vector<ISystem::ID> required_systems() const;
};