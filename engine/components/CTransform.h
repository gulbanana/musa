#pragma once
#include <engine/geometry.h>

class CTransform : public Identified<IComponent, CMP::Transform>
{
public:
	ITransform* matrix;

	CTransform(ITransform* spec) : matrix(spec) {}
};

