#pragma once
#include <functional>
#include "IGraphWalker.h"

class LambdaWalker : public IGraphWalker
{
	std::function<void(LeafNode*)> _leafCallback;
	std::function<void(BranchNode*)> _branchCallback;

public:
	LambdaWalker(std::function<void(LeafNode*)>, std::function<void(BranchNode*)>);
	virtual void visit(BranchNode* node) override;
	virtual void visit(LeafNode* node) override;
};

