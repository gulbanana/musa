#include <core/stdafx.h>
#include "ThreadedSystemBase.h"

ThreadedSystemBase::ThreadedSystemBase(void) {}

ThreadedSystemBase::~ThreadedSystemBase(void) {}

void ThreadedSystemBase::on_frame()
{
	on_wake();
}