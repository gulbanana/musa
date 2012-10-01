#pragma once
#include <memory>
#include <engine/core.h>
#include <engine/geometry.h>

template<typename TBounds>
class CExtents : public Identified<IComponent, CMP::Extents>
{
public:
	std::shared_ptr<IBounded<TBounds>> bounds;
	CExtents(std::shared_ptr<IBounded<TBounds>> b) : bounds(b) {}
};

