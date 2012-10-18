#include <engine/core.h>
#include <engine/components.h>
#include <engine/misc.h>
#include "RootNode.h"
using namespace std;

RootNode::RootNode()
{ 
	add_component(make_unique<CScene>());
}

RootNode::~RootNode()
{
}

void RootNode::accept(IGraphWalker* visitor)
{ 
	visitor->visit(this); 
}