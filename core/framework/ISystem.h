#pragma once
#include <SDL_events.h>
#include "IEntity.h"

class ISystem : public Identifiable<ISystem>
{
public:
	virtual ~ISystem() {}

    //systems can express ordering requirements
    virtual std::vector<ISystem::ID> required_systems() const = 0;

	//systems can optionally process frames or events
	virtual void on_frame() {};
	virtual void on_message() {};
	virtual bool on_event(SDL_Event& event) { return false; };

	//systems are notified of all entities; subclasses manage requirements
	virtual void on_entity(std::weak_ptr<IEntity> new_entity) {};
};