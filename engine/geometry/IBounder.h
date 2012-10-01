#pragma once
struct CircleMesh;
struct SphereMesh;
struct RectangleMesh;
struct RectangularPrism;
struct FVMesh;

template<typename TBounds>
class IBounder
{
public:
	virtual ~IBounder() {}

	virtual TBounds visit(CircleMesh*) = 0;
	virtual TBounds visit(SphereMesh*) = 0;
	virtual TBounds visit(RectangleMesh*) = 0;
	virtual TBounds visit(RectangularPrismMesh*) = 0;
	virtual TBounds visit(FVMesh*) = 0;
};