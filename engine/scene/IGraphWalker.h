#pragma once

class BranchNode;
class LeafNode;

class IGraphWalker
{
public:
	virtual ~IGraphWalker();
	virtual void visit(BranchNode* node) = 0;
	virtual void visit(LeafNode* node) = 0;
};