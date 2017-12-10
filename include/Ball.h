#pragma once
#include "SBTAbstractAnimatedNode.h"
#include "LayerNode.h"

class Ball :
	public SBTAbstractAnimatedNode
{
public:
	Ball(GraphicResourceHolder& textures, sf::Vector2f center);

	void					drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	//
	sf::FloatRect			getGlobalBounds() const;
	
	int				getNodeType() const;
	
	int			getActionType() const;

	virtual void			centerOrigin();
	
	void					setMaster(int type);
	
	int			getMaster(){return m_master;}
protected:
	void					updateCurrent(sf::Time dt);
private:
	int			m_master;
};

