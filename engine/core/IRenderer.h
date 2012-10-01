#pragma once
#include "Circle.h"
#include "Rectangle.h"
#include "Polygon.h"

class IRenderer
{
public:
	virtual ~IRenderer() = 0 {}

	virtual void visit(Circle*) = 0;
	virtual void visit(Rectangle*) = 0;
	virtual void visit(Polygon*) = 0;
};