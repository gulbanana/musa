#pragma once
#include <engine/geometry.h>

class CCamera : public Identified<IComponent, CMP::Camera>
{
public:
	IRenderable* view;

	CCamera(IRenderable* camera) : view(camera) {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CCamera(*this)); }
};

