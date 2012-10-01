#pragma once
#include <vector>
#include <memory>
#include <engine/geometry.h>
#include "IComponent.h"

template<typename TBounds>
class CExtents : public Identified<IComponent, CID::Extents>
{
public:
	std::shared_ptr<IBounded<TBounds>> bounds;
	CExtents(std::shared_ptr<IBounded<TBounds>> b) : bounds(b) {}
};

