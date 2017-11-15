#include "SBTAbstractSceneNode.h"

class Pred
{
public:
	explicit Pred(const SBTAbstractSceneNode& node):node(&node){}
	bool operator() (SBTAbstractSceneNode::Ptr& n)
	{
		return (n.get() == node);
	}
private:
	const SBTAbstractSceneNode* node;
};

SBTAbstractSceneNode::SBTAbstractSceneNode():
		mParent(nullptr), mBody(nullptr)
{
}

SBTAbstractSceneNode::~SBTAbstractSceneNode()
{
}

void SBTAbstractSceneNode::attachChild(Ptr Child)
{
	mChildren.push_back(std::move(Child));
}

SBTAbstractSceneNode::Ptr SBTAbstractSceneNode::detachChild(const SBTAbstractSceneNode& Child)
{
	auto tmp = std::find_if(mChildren.begin(), mChildren.end(), Pred(Child));
	assert(tmp != mChildren.end());
	Ptr result = std::move(*tmp);
	result->mParent = nullptr;
	mChildren.erase(tmp);
	return result;
}

void SBTAbstractSceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	drawCurrent(target, states);
	for(auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
	{
		(*itr)->draw(target,states);
	}
}

void SBTAbstractSceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	for(auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
	{
		(*itr)->update(dt);
	}
}

void SBTAbstractSceneNode::updateCurrent(sf::Time dt)
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

sf::Transform SBTAbstractSceneNode::getWorldTransform() const
{
	sf::Transform result = sf::Transform::Identity;
	for(const SBTAbstractSceneNode* node = this; node != nullptr; node = node->mParent)
	{
		result = node->getTransform() * result;
	}
	return result;
}

sf::Vector2f SBTAbstractSceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

int SBTAbstractSceneNode::getActionType() const
{
	return 0;
}

void SBTAbstractSceneNode::onCommand(const SBTCommand& command, sf::Time dt)
{
	if (command.category == getActionType())
		command.action(*this, dt);
	std::for_each(mChildren.begin(), mChildren.end(), [&command,dt](Ptr& child)mutable{child->onCommand(command,dt);});
}

sf::FloatRect SBTAbstractSceneNode::getGlobalBounds() const
{
	return sf::FloatRect();
}

bool collision(const SBTAbstractSceneNode& lhs, const SBTAbstractSceneNode& rhs)
{
	return lhs.getGlobalBounds().intersects(rhs.getGlobalBounds());
}

void SBTAbstractSceneNode::checkNodeCollision(SBTAbstractSceneNode& node, std::set<SBTAbstractSceneNode::Pair>& collisions)
{
	if (this != &node && collision(*this, node)) 
		collisions.insert(std::minmax(this, &node));

	std::for_each(mChildren.begin(), mChildren.end(), [&node, &collisions](Ptr& ptr_child){ptr_child->checkNodeCollision(node, collisions);});
}

void SBTAbstractSceneNode::checkSceneCollision(SBTAbstractSceneNode& node, std::set<Pair>& collisions)
{
	checkNodeCollision(node, collisions);

	std::for_each(node.mChildren.begin(), node.mChildren.end(), [&node, &collisions, this](Ptr& ptr_child){this->checkSceneCollision(*ptr_child, collisions);});
}

bool SBTAbstractSceneNode::isMarkedForRemove()
{
	return false;
}

void SBTAbstractSceneNode::removeWrecks()
{
	//
	std::for_each(mChildren.begin(), mChildren.end(), [](Ptr& node){if (node->isMarkedForRemove()) node->removeBody() ;});
	//
	auto itr = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&SBTAbstractSceneNode::isMarkedForRemove));
	mChildren.erase(itr, mChildren.end());
	std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&SBTAbstractSceneNode::removeWrecks));
}

void SBTAbstractSceneNode::setBody(b2Body* b_ptr)
{
	mBody = b_ptr;
	mBody->SetUserData(this);
}

void SBTAbstractSceneNode::SetLinearVelocity(b2Vec2 vel)
{
	mBody->SetLinearVelocity(vel);
}

void SBTAbstractSceneNode::removeBody()
{
	mBody->GetWorld()->DestroyBody(mBody);
}