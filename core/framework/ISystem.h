#pragma once
#include <SDL_events.h>
#include "IEntity.h"

class ISystem : public Identifiable<ISystem>
{
public:
	virtual ~ISystem() {}

    //systems are self-describing, with ordering requirements
    virtual std::string description() const = 0;
    virtual std::vector<ISystem::ID> required_systems() const = 0;

	//systems can optionally process frames or events
	virtual void on_frame() {};
	virtual void on_message() {};
	virtual bool on_event(SDL_Event& event) { return false; };

	//systems are notified of all entities; subclasses manage requirements
	virtual void on_entity(std::weak_ptr<IEntity> new_entity) {};
};

namespace std
{
    std::string to_string(ISystem* system);
}