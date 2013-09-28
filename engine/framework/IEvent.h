#pragma once
#include "Identified.h"

enum class EVT
{
	Quit,
	COUNT
};

class IEvent : Identifiable<EVT>
{
};