#include <engine/core.h>
#include "ThreadedSystemBase.h"

ThreadedSystemBase::ThreadedSystemBase(void)
{
}


ThreadedSystemBase::~ThreadedSystemBase(void)
{
}

void ThreadedSystemBase::on_frame()
{
	on_wake();
}

void ThreadedSystemBase::on_message()
{
	//XXX implement messages
}

bool ThreadedSystemBase::on_event(SDL_Event& event)
{
	//XXX maybe remove this
	return false;
}

void ThreadedSystemBase::add_entity(std::weak_ptr<IEntity> new_entity) {}