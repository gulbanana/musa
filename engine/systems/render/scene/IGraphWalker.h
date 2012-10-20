#pragma once

class RootNode;
class BranchNode;
class LeafNode;

class IGraphWalker
{
public:
	virtual ~IGraphWalker() {}
	virtual void visit(RootNode* node) = 0;
	virtual void visit(BranchNode* node) = 0;
	virtual void visit(LeafNode* node) = 0;
};