#pragma once
#include "SpriteNode.h"

class Wall:public SpriteNode
{
public:
	Wall();
	~Wall();
	virtual RecieverType getActionType() const;
	virtual NodeType getNodeType() const;
};

