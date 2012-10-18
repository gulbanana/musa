#include <engine/core.h>
#include "LambdaWalker.h"
#include "BranchNode.h"

LambdaWalker::LambdaWalker(std::function<void(LeafNode*)> leafFunc, std::function<void(BranchNode*)> branchFunc)
	: _leafCallback(leafFunc), _branchCallback(branchFunc) {}

void LambdaWalker::visit(BranchNode* node)
{
	_branchCallback(node);
	for (auto child : node->children)
	{
		child->accept(this);
	}
}

void LambdaWalker::visit(LeafNode* node)
{
	_leafCallback(node);
}