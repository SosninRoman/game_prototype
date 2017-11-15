#include "LayerNode.h"

LayerNode::LayerNode():
        SBTAbstractSceneNode()
{
}

LayerNode::~LayerNode()
{
}

int LayerNode::getActionType() const
{
	return RecieverType::SceneRecieverType;
}

int LayerNode::getNodeType() const
{
	return NodeType::SceneNodeType;
}

bool LayerNode::isMarkedForRemove()
{
	return false;
}