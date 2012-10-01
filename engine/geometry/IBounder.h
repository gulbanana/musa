#pragma once
struct CircleMesh;
struct RectangleMesh;
struct FVMesh;

template<typename TBounds>
class IBounder
{
public:
	virtual ~IBounder() = 0 {}

	virtual TBounds visit(CircleMesh*) = 0;
	virtual TBounds visit(RectangleMesh*) = 0;
	virtual TBounds visit(FVMesh*) = 0;
};