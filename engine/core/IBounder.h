#pragma once
#include "Circle.h"
#include "Rectangle.h"
#include "Polygon.h"

template<typename TBounds>
class IBounder
{
public:
	virtual ~IBounder() = 0 {}

	virtual typename TBounds visit(Circle*) = 0;
	virtual typename TBounds visit(Rectangle*) = 0;
	virtual typename TBounds visit(Polygon*) = 0;
};