#include "SceneNode.h"
#include <assert.h>

class Pred
{
public:
	Pred(const SceneNode& node):node(&node){}
	bool operator() (SceneNode::Ptr& n)
	{
		return (n.get() == node);
	}
private:
	const SceneNode* node;
};

void SceneNode::attachChild(Ptr Child)
{
	mChildren.push_back(std::move(Child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& Child)
{
	auto tmp = std::find_if(mChildren.begin(), mChildren.end(), Pred(Child));
	assert(tmp != mChildren.end());
	Ptr result = std::move(*tmp);
	result->mParent = nullptr;
	mChildren.erase(tmp);
	return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	drawCurrent(target, states);
	for(auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
	{
		(*itr)->draw(target,states);
	}
}



void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	for(auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
	{
		(*itr)->update(dt);
	}
}


sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform result = sf::Transform::Identity;
	for(const SceneNode* node = this; node != nullptr; node = node->mParent)
	{
		result = node->getTransform() * result;
	}
	return result;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}