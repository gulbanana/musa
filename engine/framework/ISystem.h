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
	COUNT
};

class ISystem : public Identifiable<SYS>
{
public:
	//Systems can optionally process frames or SDL events
	virtual ~ISystem() {}
	virtual void on_frame() = 0;
	virtual void on_message() = 0;
	virtual bool on_event(SDL_Event& event) = 0;

	//systems are notified of all entities; subclasses manage requirements
	virtual void add_entity(std::weak_ptr<IEntity> new_entity) = 0;
};