#pragma once
#include "SBTAbstractSpriteNode.h"
#include "LayerNode.h"

class Wall:public SBTAbstractSpriteNode
{
public:
	Wall();
	~Wall();
	virtual int getActionType() const;
	virtual int getNodeType() const;
};

