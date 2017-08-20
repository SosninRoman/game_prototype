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

void SceneNode::updateCurrent(sf::Time dt)
{
	if(mBody != nullptr)
	{
		auto p = mBody->GetPosition().x;
		auto pp = mBody->GetPosition().y;
		auto act = mBody->IsActive();
		auto awak = mBody->IsAwake();
		auto vel = mBody->GetLinearVelocity();
		setPosition( metr_to_pixel(mBody->GetPosition().x), metr_to_pixel(mBody->GetPosition().y) );
		setRotation(mBody->GetAngle() * 180 / b2_pi);
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

RecieverType SceneNode::getActionType() const
{
	return RecieverType::Scene;
}

NodeType SceneNode::getNodeType() const
{
	return NodeType::Scene;
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
	if (command.category == getActionType())
		command.action(*this, dt);
	std::for_each(mChildren.begin(), mChildren.end(), [&command,dt](Ptr& child)mutable{child->onCommand(command,dt);});
}

sf::FloatRect SceneNode::getGlobalBounds() const
{
	return sf::FloatRect();
}

bool collision(const SceneNode& lhs, const SceneNode& rhs)
{
	return lhs.getGlobalBounds().intersects(rhs.getGlobalBounds());
}

void SceneNode::checkNodeCollision(SceneNode& node, std::set<SceneNode::Pair>& collisions)
{
	if (this != &node && collision(*this, node)) 
		collisions.insert(std::minmax(this, &node));

	std::for_each(mChildren.begin(), mChildren.end(), [&node, &collisions](Ptr& ptr_child){ptr_child->checkNodeCollision(node, collisions);});
}

void SceneNode::checkSceneCollision(SceneNode& node, std::set<Pair>& collisions)
{
	checkNodeCollision(node, collisions);

	std::for_each(node.mChildren.begin(), node.mChildren.end(), [&node, &collisions, this](Ptr& ptr_child){this->checkSceneCollision(*ptr_child, collisions);});
}

bool SceneNode::isMarkedForRemove()
{
	return false;
}

void SceneNode::removeWrecks()
{
	auto itr = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::isMarkedForRemove));
	mChildren.erase(itr, mChildren.end());
	std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::removeWrecks));
}

void SceneNode::setBody(b2Body* b_ptr)
{
	mBody = b_ptr;
	mBody->SetUserData(this);
}

void SceneNode::SetLinearVelocity(b2Vec2 vel)
{
	mBody->SetLinearVelocity(vel);
}