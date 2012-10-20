#pragma once
#include <functional>
#include "IGraphWalker.h"

class LambdaWalker : public IGraphWalker
{
	std::function<void(RootNode*)> _root_callback;
	std::function<void(BranchNode*)> _branch_callback;
	std::function<void(LeafNode*)> _leaf_callback;

public:
	LambdaWalker(std::function<void(RootNode*)>,std::function<void(BranchNode*)>,std::function<void(LeafNode*)>);
	virtual void visit(RootNode* node) override;
	virtual void visit(BranchNode* node) override;
	virtual void visit(LeafNode* node) override;
};

