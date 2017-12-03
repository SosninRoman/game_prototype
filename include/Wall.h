#pragma once
#include "SBTAbstractUnvisibleNode.h"
#include "LayerNode.h"

class Wall:public SBTAbstractUnvisibleNode
{
public:
	Wall();
	~Wall() override;
	int getActionType() const override;
	int getNodeType() const override;
};

