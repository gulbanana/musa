#pragma once
#include <memory>
#include <vector>
#include "IComponent.h"

class CMesh : public Identified<IComponent, CID::Mesh>
{
public:
	std::vector<std::unique_ptr<IRenderable<Rect4F>>> polys;
	Color4F color;

	CGeometry2D(Color4F c, std::unique_ptr<IRenderable<Rect4F>> p);
	Rect4F bounds();
};

