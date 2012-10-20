#include <engine/core.h>
#include "LambdaWalker.h"
#include "RootNode.h"
#include "BranchNode.h"

LambdaWalker::LambdaWalker(std::function<void(RootNode*)> rootFunc,
						   std::function<void(BranchNode*)> branchFunc,
						   std::function<void(LeafNode*)> leafFunc)
	: _leaf_callback(leafFunc), _branch_callback(branchFunc), _root_callback(rootFunc) {}

void LambdaWalker::visit(RootNode* node)
{
	_root_callback(node);
	for (auto& child : node->children)
	{
		child->accept(this);
	}
}

void LambdaWalker::visit(BranchNode* node)
{
	_branch_callback(node);
	for (auto& child : node->children)
	{
		child->accept(this);
	}
}

void LambdaWalker::visit(LeafNode* node)
{
	_leaf_callback(node);
}