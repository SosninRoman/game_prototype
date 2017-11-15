#pragma once
#include <vector>
#include <memory>
#include <set>
#include <algorithm>
#include "SBTCommand.h"
#include "SBTAbstractSceneNode.h"
#include "RecieverTypeEnum.h"

enum NodeType
{
	NoneNodeType = 0,
	SceneNodeType = 1,
	PaddleNodeType = 1 << 1,
	BallNodeType = 1 << 2,
	CubeNodeType = 1 << 3,
	WallNodeType = 1 << 4,
};

class LayerNode: public SBTAbstractSceneNode
{
public:

	LayerNode();

	~LayerNode() override;

	int             getActionType() const override;

    int     		getNodeType() const override;

	bool			isMarkedForRemove() override;
};

