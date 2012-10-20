#pragma once
#include <engine/geometry.h>

class CTransform : public Identified<IComponent, CMP::Transform>
{
public:
	IRenderable* view;

	CTransform(IRenderable* camera) : view(camera) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CTransform(*this)); }
};

